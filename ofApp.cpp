#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_SUBTRACT);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	
	int radius = 250;
	float handle_len = radius * 0.5522;
	int number_of_location = 6;
	int deg_span = 360 / number_of_location;
	ofColor color;

	for (int k = 0; k < 5; k++) {

		color.setHsb(ofMap(k, 0, 5, 0, 255), 255, 255);
		ofSetColor(color);

		vector<glm::vec2> location_list;
		vector<float> deg_list;
		for (int deg = 0; deg < 360; deg += deg_span) {

			location_list.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
			deg_list.push_back(deg + 90);
		}

		for (int i = 0; i < location_list.size(); i++) {

			deg_list[i] += ofMap(ofNoise(glm::vec3(location_list[i] * 0.005, k * 0.03 + ofGetFrameNum() * 0.008)), 0, 1, -120, 120);
		}

		ofNoFill();
		ofSetLineWidth(2);

		ofBeginShape();
		for (int i = 0; i < location_list.size(); i++) {

			int n = (i + 1) % location_list.size();

			ofVertex(location_list[i]);
			ofBezierVertex(
				location_list[i] + glm::vec2(handle_len * cos(deg_list[i] * DEG_TO_RAD), handle_len * sin(deg_list[i] * DEG_TO_RAD)),
				location_list[n] + glm::vec2(handle_len * cos((deg_list[n] + 180) * DEG_TO_RAD), handle_len * sin((deg_list[n] + 180) * DEG_TO_RAD)),
				location_list[n]);
		}
		ofEndShape();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}