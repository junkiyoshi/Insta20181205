#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);
	ofSetCircleResolution(36);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->locations.clear();

	for (int i = 0; i < 39; i++) {

		glm::vec2 location = glm::vec2(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, 0, ofGetWidth()), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, 0, ofGetHeight()));
		this->locations.push_back(location);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	float radius = 20;
	for (int i = 0; i < this->locations.size(); i++) {

		ofNoFill();
		ofDrawCircle(this->locations[i], radius);

		vector<glm::vec2> near_locations;
		for (int j = 0; j < this->locations.size(); j++) {

			if (i == j) {

				continue;
			}

			glm::vec2 distance = this->locations[i] - this->locations[j];
			float distance_lenght = glm::length(distance);

			if (distance_lenght < 80) {

				near_locations.push_back(this->locations[j]);
			}
		}

		if (near_locations.size() > 0) {

			int span = PI / near_locations.size();
			for (int j = 0; j < near_locations.size(); j++) {

				float angle = std::atan2(near_locations[j].y - this->locations[i].y, near_locations[j].x - this->locations[i].x);
				float near_angle = std::atan2(this->locations[i].y - near_locations[j].y, this->locations[i].x - near_locations[j].x);

				glm::vec2 point = this->locations[i] + glm::vec2(radius * cos(angle), radius * sin(angle));
				glm::vec2 near_point = near_locations[j] + glm::vec2(radius * cos(near_angle), radius * sin(near_angle));

				ofDrawLine(point, near_point);

				ofFill();
				ofBeginShape();
				for (float rad = near_angle - PI / 6; rad < near_angle + PI / 6; rad += PI / 360) {

					ofVertex(near_locations[j] + glm::vec2(radius * 0.8 * cos(rad), radius * 0.8 * sin(rad)));
				}
				ofVertex(near_locations[j]);
				ofEndShape(true);
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}