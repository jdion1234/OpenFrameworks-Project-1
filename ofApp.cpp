#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	//Basic Setup
	ofBackground(255);
	ofSetCircleResolution(100);

	// Initialize Global Variables
	this->border_circle_radius = 20;
	this->outer_sin_radius = 500;
	this->outer_cos_radius = 500;
	this->resolution = .005;
	this->timer1 = 0;
	this->timer2 = 79;
	this->offset = .05;

	// Noise 1 Setup
	this->ring_noise1 = 0;
	this->ring_noise_size1 = .8;
	this->ring_noise_timer1 = 0;
	this->ring_noise_timesize1 = 35;
	this->ring_noise_on1 = false;

	// Noise 2 Setup
	this->ring_noise2 = 0;
	this->ring_noise_size2 = ring_noise_size1 * .8;
	this->ring_noise_timer2 = 0;
	this->ring_noise_timesize2 = ring_noise_timesize1 / 2;
	this->ring_noise_on2 = false;

	// Noise 3 Setup
	this->ring_noise3 = 0;
	this->ring_noise_size3 = ring_noise_size1 * .5;
	this->ring_noise_timer3 = 0;
	this->ring_noise_timesize3 = ring_noise_timesize1 / 3;
	this->ring_noise_on3 = false;

	// Noise 4 Setup
	this->ring_noise4 = 0;
	this->ring_noise_size4 = ring_noise_size1 * .5;
	this->ring_noise_timer4 = 0;
	this->ring_noise_timesize4 = ring_noise_timesize1 / 3;
	this->ring_noise_on4 = false;

	// Noise 5 Setup
	this->ring_noise5 = 0;
	this->ring_noise_size5 = ring_noise_size1 * .5;
	this->ring_noise_timer5 = 0;
	this->ring_noise_timesize5 = ring_noise_timesize1 / 3;
	this->ring_noise_on5 = false;

	// Generate Circle
	float i = 0;
	int counter = 0;

	while (i < M_TWO_PI) {

		locations_vector.push_back(glm::vec3(outer_sin_radius * sin(i), outer_cos_radius * cos(i), 0));
		i += resolution;
		counter++;
	}




}

//--------------------------------------------------------------
void ofApp::update() {

	this->timer1 += .05;
	this->timer2 += 1;
	this->timer3 += 1;
	this->outer_cos_radius = ofMap(sin(timer1), -1, 1, 480, 520);
	this->outer_sin_radius = ofMap(sin(timer1 + (PI / 2)), -1, 1, 480, 520);
	this->color_change = ofMap(sin(timer1 + (PI / 2)), -1, 1, 150, 250);
	this->locations_vector.clear();
	this->colors_vector.clear();

	// Noise 1 Timer
	if (timer2 % 80 == 0) {
		ring_noise_on1 = true;
		this->ring_noise1 = ofRandom(M_TWO_PI - ring_noise_size1 - .1);

	}

	// Noise 2 Timer
	if ((timer2 + 40) % 80 == 0) {
		ring_noise_on2 = true;
		if (ring_noise1 <= PI) {
			ring_noise2 = ring_noise1 + PI;
		}
		else {
			ring_noise2 = ring_noise1 - PI;
		}

		if (ring_noise2 >= (M_TWO_PI - ring_noise_size2)) {
			ring_noise2 = M_TWO_PI - ring_noise_size2 - .1;
		}

	}

	// Noise 3 Timer
	if ((timer2 - 40) % 80 == 0) {
		ring_noise_on3 = true;
		this->ring_noise3 = ofRandom(4);
	}

	// Noise 4 Timer
	if ((timer2 - 50) % 80 == 0) {
		ring_noise_on4 = true;
		this->ring_noise4 = ring_noise3 + .1 + ring_noise_size3;

	}

	// Noise 5 Timer
	if ((timer2 - 60) % 80 == 0) {
		ring_noise_on5 = true;
		this->ring_noise5 = ring_noise4 + .1 + ring_noise_size3;
	}

	float i = 0;
	int counter = 0;

	while (i < M_TWO_PI) {

		float border_noise = ofMap(ofNoise(sin(i + (timer1 / 5)), cos(i + (timer1 / 5)), timer1 / 5), 0, 1, 1 - offset, 1 + offset);

		glm::vec3 location_color;
		glm::vec3 location_coordinates;
		location_color = glm::vec3(color_change, 100, 150);
		location_coordinates = glm::vec3(border_noise * outer_sin_radius * sin(i), border_noise * outer_cos_radius * cos(i), 0);

		// Noise 1
		if ((i >= ring_noise1) && (i <= (ring_noise1 + ring_noise_size1)) && ring_noise_on1 == true) {

			float bump = calculateBump(i, ring_noise1, ring_noise_size1, ring_noise_timer1, ring_noise_timesize1);
			float color_bump = calculateColorBump(i, ring_noise1, ring_noise_size1, ring_noise_timer1, ring_noise_timesize1);
			float g = ofMap(color_bump, 0, 255, 0, 155);
			location_coordinates = bump * location_coordinates;
			location_color = glm::vec3(color_change, 100 + g, 150);

		}

		// Noise2
		if ((i >= ring_noise2) && (i <= (ring_noise2 + ring_noise_size2)) && ring_noise_on2 == true) {

			float bump = calculateBump(i, ring_noise2, ring_noise_size2, ring_noise_timer2, ring_noise_timesize2);
			float color_bump = calculateColorBump(i, ring_noise2, ring_noise_size2, ring_noise_timer2, ring_noise_timesize2);
			float g = ofMap(color_bump, 0, 255, 0, 155);
			float b = ofMap(color_bump, 0, 255, 0, 105);
			location_coordinates = bump * location_coordinates;
			location_color = glm::vec3(color_change, 100 + g, 150 + b);


		}

		// Noise 3
		if ((i >= ring_noise3) && (i <= (ring_noise3 + ring_noise_size3)) && ring_noise_on3 == true) {

			float bump = calculateBump(i, ring_noise3, ring_noise_size3, ring_noise_timer3, ring_noise_timesize3);
			float color_bump = calculateColorBump(i, ring_noise3, ring_noise_size3, ring_noise_timer3, ring_noise_timesize3);
			float r = ofMap(color_bump, 0, 255, 0, 55);
			float b = ofMap(color_bump, 0, 255, 0, 55);
			location_coordinates = bump * location_coordinates;
			location_color = glm::vec3(color_change, 100 + r, 150 + b);

		}

		// Noise 4
		if ((i >= ring_noise4) && (i <= (ring_noise4 + ring_noise_size4)) && ring_noise_on4 == true) {

			float bump = calculateBump(i, ring_noise4, ring_noise_size4, ring_noise_timer4, ring_noise_timesize4);
			float color_bump = calculateColorBump(i, ring_noise4, ring_noise_size4, ring_noise_timer4, ring_noise_timesize4);
			float r = ofMap(color_bump, 0, 255, 0, 255 - color_change);
			float b = ofMap(color_bump, 0, 255, 0, 105);
			location_coordinates = bump * location_coordinates;
			location_color = glm::vec3(color_change + r, 100, 150 + b);

		}

		// Noise 5
		if ((i >= ring_noise5) && (i <= (ring_noise5 + ring_noise_size5)) && ring_noise_on5 == true) {

			float bump = calculateBump(i, ring_noise5, ring_noise_size5, ring_noise_timer5, ring_noise_timesize5);
			float color_bump = calculateColorBump(i, ring_noise5, ring_noise_size5, ring_noise_timer5, ring_noise_timesize5);
			float r = ofMap(color_bump, 0, 255, 0, 255 - color_change);
			float b = ofMap(color_bump, 0, 255, 0, 105);
			location_coordinates = bump * location_coordinates;
			location_color = glm::vec3(color_change + r, 100, 150 + b);

		}

		locations_vector.push_back(location_coordinates);
		colors_vector.push_back(location_color);


		i += resolution;
		counter++;
	}

	// Noise 1 timer
	if (ring_noise_on1) {
		ring_noise_timer1++;
	}
	if (ring_noise_timer1 > ring_noise_timesize1) {
		ring_noise_on1 = false;
		ring_noise_timer1 = 0;
	}


	// Noise 2 timer
	if (ring_noise_on2) {
		ring_noise_timer2++;
	}
	if (ring_noise_timer2 > ring_noise_timesize2) {
		ring_noise_on2 = false;
		ring_noise_timer2 = 0;
	}

	// Noise 3 timer
	if (ring_noise_on3) {
		ring_noise_timer3++;
	}
	if (ring_noise_timer3 > ring_noise_timesize3) {
		ring_noise_on3 = false;
		ring_noise_timer3 = 0;
	}

	// Noise 4 timer
	if (ring_noise_on4) {
		ring_noise_timer4++;
	}
	if (ring_noise_timer4 > ring_noise_timesize4) {
		ring_noise_on4 = false;
		ring_noise_timer4 = 0;
	}

	// Noise 5 timer
	if (ring_noise_on5) {
		ring_noise_timer5++;
	}
	if (ring_noise_timer5 > ring_noise_timesize5) {
		ring_noise_on5 = false;
		ring_noise_timer5 = 0;
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	cam.begin();
	ofHideCursor();

	for (int i = 0; i < locations_vector.size(); i++) {
		ofSetColor((int)colors_vector[i].x, (int)colors_vector[i].y, (int)colors_vector[i].z);
		ofDrawSphere(locations_vector[i], border_circle_radius);
	}

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

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
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

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

float ofApp::calculateBump(float current_location, float noise_location_start, float noise_width, int noise_time_count, int noise_time_length) {


	float range = ofMap(current_location, noise_location_start, noise_location_start + noise_width, -3, 3);
	float timerange = ofMap(noise_time_count, 0, noise_time_length, -PI / 2, (3 * PI) / 2);
	float time = ofMap(sin(timerange), -1, 1, 1, 1.4);

	return ofMap((.125) / ((range * range) + (.25)), .0135135, .5, 1, time);

}


float ofApp::calculateColorBump(float current_location, float noise_location_start, float noise_width, int noise_time_count, int noise_time_length) {

	float timerange = ofMap(noise_time_count, 0, noise_time_length, -PI / 2, (3 * PI) / 2);
	float color_sin_value = ofMap(current_location, noise_location_start, noise_location_start + noise_width, -PI / 2, (3 * PI) / 2);
	float color_height = ofMap(sin(color_sin_value), -1, 1, 0, 256);

	return ofMap(sin(timerange), -1, 1, 0, color_height);


}

