#include "ofApp.h"


using namespace scythe;
using namespace std;


//--------------------------------------------------------------
void ofApp::setup() {
    y = seqa(5, 1, n);
    X = Matrix<double>(n, 3, false);
    X = 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 0, 1, 0, 1, 0;
    poisson_model.y_ = y;
    poisson_model.X_ = X;

    theta = invpd(crossprod(X)) * t(X) * log(y);
    beta_MLE = BFGS(poisson_model, theta, myrng, 100, 1e-5, true);
    beta_bs_store = Matrix<double>(M, 3);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

    if (i < M) {
        Matrix<double> eta = X * beta_MLE;
        Matrix<double> m = exp(eta);
        for (int j = 0; j < n; ++j)
            poisson_model.y_(j) = myrng.rpois(m(j));

        beta_bs_store(i, _) = BFGS(poisson_model, beta_MLE, myrng, 100, 1e-5);
        i++;
    }




    //cout << "The MLEs are: " << endl;
    //std::cout << t(beta_MLE) << "\n";
    //cout << "The bootstrap SEs are: " << endl;


    //beta_bs_store is M x n matrix
    for (int c = 0; c < beta_bs_store.cols(); c ++) {
        //ofDrawBitmapString(sdc(beta_bs_store)(0,c), c*10 + 10, 10 * 10);
        float top = ofMap(sdc(beta_bs_store)(0,c), 0,1, ofGetHeight(),0);
        float left = ofMap(c, 0, beta_bs_store.cols(), 0, ofGetWidth());
        ofSetColor(255);
        ofFill();
        ofRect(left, top, ofGetWidth()/beta_bs_store.cols(), ofGetHeight()-top);
    }

    //std::cout<<sdc(beta_bs_store)<< "\n";



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
