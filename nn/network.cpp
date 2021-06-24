
#include "network.h"

Network::Network() {}

Network::Network( int*  nodes_per_layer, int len)
      : npl(nodes_per_layer), num_layers(len-1), l_rate(0.2) {
   weights = new Matrix[num_layers];
   bias = new Matrix[num_layers];
   for (int i = 0; i < num_layers; i++) {
      weights[i] = Matrix(npl[i+1], npl[i]);
      weights[i].randomize();
      bias[i] = Matrix(npl[i+1], 1);
      bias[i].randomize();
   }
}

Network::~Network() {
   delete [] weights;
   delete [] bias;
}

void Network::feed(float** data, int n) {
   Matrix *cal_weights = new Matrix[num_layers];
   Matrix *sig = new Matrix[num_layers];
   Matrix *err = new Matrix[num_layers];
   for (int i = 0; i < n; i++) {
      // FEED FORWARD
      Matrix input(data[i], 0, npl[0]);
      cal_weights[0] = Matrix::multiply(weights[0], input);
      cal_weights[0].add(bias[0]);
      sig[0] = Matrix::sigmoid(cal_weights[0]);
      for (int j = 1; j < num_layers; j++) {
         cal_weights[j] = Matrix::multiply(weights[j], sig[j-1]);
         cal_weights[j].add(bias[j]);
         sig[j] = Matrix::sigmoid(cal_weights[j]);
      }

      // Error
      Matrix actual(data[i], npl[0], npl[num_layers]);
      err[num_layers - 1] = Matrix::subtract(actual, sig[num_layers - 1]);
      for (int j = num_layers - 2; j >= 0; j--) {
         Matrix tran = Matrix::transpose(weights[j+1]);
         err[j] = Matrix::multiply(tran, err[j+1]);
      }

      // Gradient
      for (int j = num_layers - 1; j >= 1; j--) {
         Matrix gradient = sig[j].derive_sigmoid();
         gradient.multiply_direct(err[j]);
         gradient.multiply_direct(l_rate);
         bias[j].add(gradient);
         Matrix tran = Matrix::transpose(cal_weights[j-1]);
         Matrix delta = Matrix::multiply(gradient, tran);
         weights[j].add(delta);
      }
      Matrix gradient = sig[0].derive_sigmoid();
      gradient.multiply_direct(err[0]);
      gradient.multiply_direct(l_rate);
      bias[0].add(gradient);
      Matrix tran = Matrix::transpose(input);
      Matrix delta = Matrix::multiply(gradient, tran);
      weights[0].add(delta);

   }
   delete [] cal_weights;
   delete [] sig;
   delete [] err;
}

void Network::print() {
   for (int i = 0; i < num_layers; i++) {
      weights[i].print();
   }
   for (int i = 0; i < num_layers; i++) {
      bias[i].print();
   }
}

Matrix Network::predict(float* data) {
   Matrix input = Matrix(data, 0, npl[0]);
   // input.print();
   for (int i = 0; i < num_layers; i++) {
      input = Matrix::multiply(weights[i], input);
      input.add(bias[i]);
      input = Matrix::sigmoid(input);
   }
   Matrix round = input.round();
   // round.print();
   return round;
}

float Network::err(float** data, int n) {
   Matrix err(npl[num_layers], 1);
   for (int i = 0; i < n; i++) {
      Matrix actual(data[i], npl[0], npl[num_layers]);
      Matrix guess = predict(data[i]);
      Matrix diff = Matrix::subtract(actual, guess);
      Matrix diff_abs = diff.abs();
      err.add(diff_abs);
   }
   // err.multiply_direct(1.0/n);
   float err_sum = err.sum();
   return err_sum/n;
}

void Network::save(const char* filename) {
   FILE* file = fopen(filename, "w");
   for (int i = 0; i < num_layers; i++) {
      weights[i].save(file);
      bias[i].save(file);
   }
   fclose(file);
}

void Network::load(const char* filename) {
   FILE* file;
   file = fopen(filename, "r");
   for (int i = 0; i < num_layers; i++) {
      weights[i].load(file);
      bias[i].load(file);
   }
   fclose(file);
}

void Network::setLearningRate(float rate) {
   l_rate = rate;
}

void Network::randomize() {
   for (int i = 0; i < num_layers; i++) {
      weights[i].randomize();
      bias[i].randomize();
   }
}

void Network::test() {
}

