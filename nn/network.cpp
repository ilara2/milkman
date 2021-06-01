

#include "network.h"


Network::Network(int _input, int _hidden, int _output) {
   // Weights
   input_weights  = Matrix(_hidden, _input);
   hidden_weights = Matrix(_output, _hidden);

   // Testing
   // float tmp1[_hidden][_input] = {
   //    {14.22898, 14.22748},
   //    {-43.98423, -41.24873}
   // };

   // float **tmp1 = new float*[_hidden];
   // //    // tmp1[0] = {14.22898, 14.22748};
   // tmp1[0] = new float[_input];
   // tmp1[0][0] = 14.22898;
   // tmp1[0][1] = 14.22748;

   // tmp1[1] = new float[_input];
   // tmp1[1][0] = -43.98423;
   // tmp1[1][1] = -41.24873;

   // float **tmp2 = new float*[_output];
   // //    // tmp1[0] = {14.22898, 14.22748};
   // tmp2[0] = new float[_hidden];
   // tmp2[0][0] = -25.61792;
   // tmp2[0][1] = -314.64670;

   // tmp2[1] = new float[_hidden];
   // tmp2[1][0] = 29.55191;
   // tmp2[1][1] = -27.42266;

   // tmp2[2] = new float[_hidden];
   // tmp2[2][0] = 60.89029;
   // tmp2[2][1] = -71.34558;


   // input_weights.data = tmp1;
   // hidden_weights.data = tmp2;

   input_weights.randomize();
   hidden_weights.randomize();

   // Bias
   hidden_bias = Matrix(_hidden, 1);
   output_bias = Matrix(_output, 1);

   hidden_bias.randomize();
   output_bias.randomize();

}

void Network::feed(int **data, int len) {

   original_input_weights  = Matrix::copy(input_weights);
   original_hidden_weights = Matrix::copy(hidden_weights);


   og_hidden_bias = Matrix::copy(hidden_bias);
   og_output_bias = Matrix::copy(output_bias);

   // for (int i = 0; i < 1; i++) {
   for (int i = 0; i < len; i++) {

      Matrix input = Matrix(data[i], 0, input_weights.cols);

      Matrix hidden = Matrix::add(Matrix::multiply(input_weights, input), hidden_bias);
      Matrix hidden_sig = Matrix::sigmoid(hidden);

      Matrix output = Matrix::add(Matrix::multiply(hidden_weights, hidden_sig), output_bias);
      Matrix output_sig = Matrix::sigmoid(output);

      Matrix actual = Matrix(data[i], input_weights.cols, hidden_weights.rows);

      // if ( (i+1) % (len/4) == 1 || i == (len-1) ) {
      //    printf("Test: %d\n", i);
      //    printf("\n\tINPUTS\n");
      //    input.print();
      //    printf("\n\tGUESS\n");
      //    output_sig.print();
      //    printf("\n\tACTUAL\n");
      //    actual.print();
      //    printf("\n\n");
      // }

      // if ( i > (len-10) ) {
      //    printf("Test: %d\n", i);
      //    printf("\n\tINPUTS\n");
      //    input.print();
      //    printf("\n\tGUESS\n");
      //    output_sig.print();
      //    printf("\n\tACTUAL\n");
      //    actual.print();
      //    printf("\n\n");
      // }

      output_error = Matrix::subtract(actual, output_sig);
      hidden_error = Matrix::multiply(Matrix::transpose(hidden_weights), output_error);


      // Hidden Weights
      Matrix gradient = Matrix::d_sigmoid(output_sig);
      gradient.multiply_direct(output_error);
      gradient.multiply((i < 100)?1.5:0.25);
      output_bias.add(gradient);
      Matrix delta_hidden_weights = Matrix::multiply(gradient, Matrix::transpose(hidden));
      hidden_weights.add(delta_hidden_weights);

      // Input Weights
      gradient = Matrix::d_sigmoid(hidden_sig);
      gradient.multiply_direct(hidden_error);
      gradient.multiply((i < 100)?1.5:0.25);
      hidden_bias.add(gradient);
      Matrix delta_input_weights = Matrix::multiply(gradient, Matrix::transpose(input));
      input_weights.add(delta_input_weights);
   }

   // input_weights.print();
   // printf("\n");
   // hidden_weights.print();
   // printf("\n");

}

Matrix Network::predict(int** data, int len) {
   Matrix err = Matrix(hidden_weights.rows, 1);
   for (int i = 0; i < len; i++) {
      Matrix input = Matrix(data[i], 0, input_weights.cols);

      Matrix hidden = Matrix::add(Matrix::multiply(input_weights, input), hidden_bias);
      Matrix hidden_sig = Matrix::sigmoid(hidden);

      Matrix output = Matrix::add(Matrix::multiply(hidden_weights, hidden_sig), output_bias);
      Matrix output_sig = Matrix::sigmoid(output); 

      Matrix actual = Matrix(data[i], input_weights.cols, hidden_weights.rows);

      err.add( Matrix::abs(Matrix::subtract(output_sig, actual) ) );

      if ( i % 400 == 0 ) {
         printf("Test: %d\n", i);
         printf("\n\tINPUTS\n");
         input.print();
         printf("\n\tGUESS\n");
         // output.print();
         output_sig.print();
         printf("\n\tACTUAL\n");
         actual.print();
         printf("\n");
         ( Matrix::abs(Matrix::subtract(output_sig, actual) ) ).print();
         printf("\n\n\n");
      }
   }

   err.multiply((1.0/len));
   // err.print();

   // input_weights.print();
   // printf("\n");
   // hidden_weights.print();
   // printf("\n");

   return err;
}

Matrix Network::predictShow(int **data, int len) {
   Matrix err = Matrix(hidden_weights.rows, 1);
   for (int i = 0; i < len; i++) {
   // for (int i = 0; i < 1; i++) {
      Matrix input = Matrix(data[i], 0, input_weights.cols);

      Matrix hidden = Matrix::add(Matrix::multiply(input_weights, input), hidden_bias);
      Matrix hidden_sig = Matrix::sigmoid(hidden);

      Matrix output = Matrix::add(Matrix::multiply(hidden_weights, hidden_sig), output_bias);
      Matrix output_sig = Matrix::sigmoid(output); 

      Matrix actual = Matrix(data[i], input_weights.cols, hidden_weights.rows);

      err.add( Matrix::abs(Matrix::subtract(output_sig, actual) ) );

      if ( i > len-25 ) {
         // printf("Test: %d\n", i);
         // printf("\n\tINPUTS\n");
         // input.print();
         // printf("\n\tGUESS\n");
         // // output.print();
         // output_sig.print();
         // printf("\n\tACTUAL\n");
         // actual.print();
         // printf("\n");
         // ( Matrix::abs(Matrix::subtract(output_sig, actual) ) ).print();
         // printf("\n\n\n");
      }
   }

   err.multiply((1.0/len));
   err.print();

   // input_weights.print();
   // printf("\n");
   // hidden_weights.print();
   // printf("\n");

   return err;
}

void Network::print() {
   printf("\n\t\tNeural Network\n\n");
   printf("Inputs\n");
   input_weights.print();
   printf("\n");
   printf("Hidden\n");
   hidden_weights.print();
   printf("\n");
}

void Network::fill() {
   input.fill();
   hidden.fill();
   output.fill();
}

void Network::randomize() {
   input_weights.randomize();
   hidden_weights.randomize();

   hidden_bias.randomize();
   output_bias.randomize();
}

void Network::goBack() {
   input_weights  = Matrix::copy(original_input_weights);
   hidden_weights = Matrix::copy(original_hidden_weights);

   hidden_bias = Matrix::copy(og_hidden_bias);
   output_bias = Matrix::copy(og_output_bias);
}

void Network::weights() {
   printf("Input Weights\n");
   input_weights.print();
   printf("\n");
   printf("Hidden Weights\n");
   hidden_weights.print();
   printf("\n");
   printf("Hidden Bias\n");
   hidden_bias.print();
   printf("\n");
   printf("Output Bias\n");
   output_bias.print();
   printf("\n");
}
