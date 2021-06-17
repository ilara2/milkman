
#include "network.h"

Network::Network(const int* const nodes_per_layer, int len)
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
      Matrix input(data[i], 0, npl[0]);
      Matrix::multiply(cal_weights[0], weights[0], input);
      cal_weights[0].add(bias[0]);
      Matrix::sigmoid(sig[0], cal_weights[0]);
      for (int j = 1; j < num_layers; j++) {
         Matrix::multiply(cal_weights[j], weights[j], sig[j-1]);
         cal_weights[j].add(bias[j]);
         Matrix::sigmoid(sig[j], cal_weights[j]);
      }
      Matrix actual(data[i], npl[0], npl[num_layers]);
      Matrix::subtract(err[num_layers-1], actual, sig[num_layers-1]);
      for (int j = num_layers-2; j >= 0; j--) {
         Matrix tran;
         Matrix::transpose(tran, weights[j+1]);
         Matrix::multiply(err[j], tran, err[j+1]);
      }
      for (int j = num_layers-1; j >= 0; j--) {
         Matrix gradient = sig[j].sigmoid();
         gradient.multiply_direct(err[j]);
         gradient.multiply_direct(l_rate);
         bias[j].add(gradient);
         Matrix delta, tran;
         Matrix::transpose(tran, cal_weights[j]);
         Matrix::multiply(delta, gradient, tran);
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

Matrix* Network::predict(float* data) {
   Matrix *input = new Matrix(data, 0, npl[0]);
   input->print();
   for (int i = 0; i < num_layers; i++) {
      Matrix t = *input;
      Matrix::multiply(*input, weights[i], t);
      input->add(bias[i]);
      t = *input;
      Matrix::sigmoid(*input, t);
   }
   return input;
}

float Network::err(float** data, int n) {
   Matrix err(npl[num_layers], 1);
   for (int i = 0; i < n; i++) {
      Matrix actual(data[i], npl[0], npl[num_layers]);
      Matrix t;
      Matrix::subtract(t, *predict(data[i]), actual);
      t = t.abs();
      err.add(t);
   }
   err.multiply_direct(1.0/n);
   float err_sum = err.sum();
   return err_sum;
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

void Network::test() {
}

