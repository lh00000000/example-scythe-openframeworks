#pragma once

#include "ofMain.h"

#include <scythestat/rng/mersenne.h>
#include <scythestat/distributions.h>
#include <scythestat/ide.h>
#include <scythestat/la.h>
#include <scythestat/matrix.h>
#include <scythestat/rng.h>
#include <scythestat/smath.h>
#include <scythestat/stat.h>
#include <scythestat/optimize.h>
#include <string>
#include <iostream>

using namespace std;
using namespace scythe;


class PoissonModel {
public:
    double operator() (const Matrix<double> beta) {
        const int n = y_.rows();
        Matrix<double> eta = X_ * beta;
        Matrix<double> m = exp(eta);
        double loglike = 0.0;
        for (int i=0; i<n; ++i)
            loglike += y_(i) * log(m(i)) - m(i);
        return -1.0 * loglike;
    }
    Matrix<double> y_;
    Matrix<double> X_;
};

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    mersenne myrng;
	const int n = 5;
	Matrix<double> y;
	Matrix<double> X;

	PoissonModel poisson_model;

	Matrix<double> theta;
	Matrix<double> beta_MLE;

	const int M = 10000;
	Matrix<double> beta_bs_store;

	int i = 0;

    ostringstream s;

};
