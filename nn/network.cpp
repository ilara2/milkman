
#include "network.h"

Network::Network(const int* const nodes_per_layer, int len)
   : npl(nodes_per_layer), num_layers(len-1), l_rate(0.1)
 {
    weights = new Matrix[num_layers];
    bias = new Matrix[num_layers];
   for (int i = 0; i < num_layers; i++) {
      weights[i] = Matrix(npl[i+1], npl[i]);
      weights[i].randomize();
      bias[i] = Matrix(npl[i+1], 1);
      bias[i].randomize();
   }
}

void Network::feed(double** data, int n) {
   Matrix *cal_weights = new Matrix[num_layers];
   Matrix *sig = new Matrix[num_layers];
   Matrix *err = new Matrix[num_layers];
   for (int i = 0; i < n; i++) {
      Matrix input(data[i], 0, npl[0]);
      cal_weights[0] = Matrix::add(Matrix::multiply(weights[0], input), bias[0]);
      sig[0] = Matrix::sigmoid(cal_weights[0]);

      for (int j = 1; j < num_layers; j++) {
         cal_weights[j] = Matrix::add(Matrix::multiply(weights[j], sig[j-1]), bias[j]);
         sig[j] = Matrix::sigmoid(cal_weights[j]);
      }

      Matrix actual(data[i], npl[0], npl[num_layers]);
      err[num_layers-1] = Matrix::subtract(actual, sig[num_layers-1]);
      for (int j = num_layers-2; j >= 0; j--) {
         err[j] = Matrix::multiply(Matrix::transpose(weights[j+1]), err[j+1]);
      }

      for (int j = num_layers-1; j >= 0; j--) {
         Matrix gradient = Matrix::d_sigmoid(sig[j]);
         gradient.multiply_direct(err[j]);
         gradient.multiply(l_rate);
         bias[j] .add(gradient);
         Matrix delta = Matrix::multiply(gradient, Matrix::transpose(cal_weights[j]));
         weights[j].add(delta);
      }
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

Matrix Network::predict(double* data) {
   Matrix input(data, 0, npl[0]);
   input.print();
   for (int i = 0; i < num_layers; i++) {
      input = Matrix::add(Matrix::multiply(weights[i], input), bias[i]);
      input = Matrix::sigmoid(input);
   }
   return input;
}

Matrix Network::err(double** data, int n) {
   Matrix err(npl[num_layers], 1);
   err.set();
   for (int i = 0; i < n; i++) {
      Matrix actual(data[i], npl[0], npl[num_layers]);
      err.add(Matrix::abs(Matrix::subtract(predict(data[i]), actual)));
   }
   float inverse = 1.0 / n;
   err.multiply(inverse);
   return err;
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
