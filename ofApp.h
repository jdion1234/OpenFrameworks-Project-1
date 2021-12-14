#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		float calculateBump(float current_location, float noise_location_start, float noise_width, int noise_time_count, int noise_time_length);
		float calculateColorBump(float current_location, float noise_location_start, float noise_width, int noise_time_count, int noise_time_length);

		// Other
		float resolution;
		float border_circle_radius;
		float outer_sin_radius;
		float outer_cos_radius;
		float offset;
		float color_change;

		// Timers
		float timer1;
		int timer2;
		int timer3;

		// Noise 1 Variables
		float ring_noise1;
		float ring_noise_size1;
		int ring_noise_timer1;
		int ring_noise_timesize1;
		bool ring_noise_on1;

		// Noise 2 Variables
		float ring_noise2;
		float ring_noise_size2;
		int ring_noise_timer2;
		int ring_noise_timesize2;
		bool ring_noise_on2;

		// Noise 3 Variables
		float ring_noise3;
		float ring_noise_size3;
		int ring_noise_timer3;
		int ring_noise_timesize3;
		bool ring_noise_on3;

		// Noise 4 Variables
		float ring_noise4;
		float ring_noise_size4;
		int ring_noise_timer4;
		int ring_noise_timesize4;
		bool ring_noise_on4;

		// Noise 5 Variables
		float ring_noise5;
		float ring_noise_size5;
		int ring_noise_timer5;
		int ring_noise_timesize5;
		bool ring_noise_on5;

		// For storing Drawing Locations And Colors
		vector <glm::vec3> locations_vector;
		vector <glm::vec3> colors_vector;

		ofEasyCam cam;

		
};
