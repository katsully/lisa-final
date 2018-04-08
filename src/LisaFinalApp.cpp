#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Kinect2.h"
#include "cinder/params/Params.h"
#include "cinder/osc/Osc.h"


using namespace ci;
using namespace ci::app;
using namespace std;

#define USE_UDP 1

#if USE_UDP
using Sender = osc::SenderUdp;
#else
using sender = osc::SenderTcp;
#endif

const std::string destinationHost = "127.0.0.1";
const uint16_t destinationPort = 10001;

class LisaFinalApp : public App {
public:
	LisaFinalApp();
	void setup() override;
	void mouseDown(MouseEvent event) override;
	void update() override;
	void draw() override;
	void shutdown();

	Sender mSender;

private:
	Kinect2::DeviceRef mDevice;
	Kinect2::BodyFrame mBodyFrame;
	ci::Channel8uRef mChannelBodyIndex;
	ci::Channel16uRef mChannelDepth;

	params::InterfaceGlRef mParams;
	bool mDrawBackground = true;
	bool mDrawSkeleton = true;
	bool mDrawPentagon = true;

	// math
	vec3 numA1;
	vec3 numA2;
	vec3 numA3;
	vec3 numA4;
	vec3 numA5;

	vec3 numB1;
	vec3 numB2;
	vec3 numB3;
	vec3 numB4;
	vec3 numB5;

	// distance between two people
	float dist1 = 0.0;
	float dist2 = 0.0;
	float dist3 = 0.0;
	float dist4 = 0.0;
	float dist5 = 0.0;

	// points for 1st person pentagon
	vec2 pointA1;
	vec2 pointA2;
	vec2 pointA3;
	vec2 pointA4;
	vec2 pointA5;

	// points for 2nd person pentagon
	vec2 pointB1;
	vec2 pointB2;
	vec2 pointB3;
	vec2 pointB4;
	vec2 pointB5;

	bool mFullScreen = true;

};

LisaFinalApp::LisaFinalApp() : mSender(8000, destinationHost, destinationPort) {
	mDevice = Kinect2::Device::create();
	mDevice->start();
	mDevice->connectBodyEventHandler([&](const Kinect2::BodyFrame frame) {
		mBodyFrame = frame;
	});
	mDevice->connectBodyIndexEventHandler([&](const Kinect2::BodyIndexFrame frame) {
		mChannelBodyIndex = frame.getChannel();
	});
	mDevice->connectDepthEventHandler([&](const Kinect2::DepthFrame frame) {
		mChannelDepth = frame.getChannel();
	});
}

void LisaFinalApp::setup()
{
	setFullScreen(mFullScreen);

	// create a parameter interface and name it
	mParams = params::InterfaceGl::create(getWindow(), "App parameters", toPixels(ivec2(200, 400)));

	// setup parameters
	mParams->addParam("Draw background", &mDrawBackground);
	mParams->addParam("Draw Skeleton", &mDrawSkeleton);
	mParams->addParam("Draw Pentagon", &mDrawPentagon);

	mParams->addSeparator();

	mParams->addParam("Distance 1", &dist1);
	mParams->addParam("Distance 2", &dist2);
	mParams->addParam("Distance 3", &dist3);
	mParams->addParam("Distance 4", &dist4);
	mParams->addParam("Distance 5", &dist5);

	mParams->addSeparator();

	mParams->addParam("Full Screen", &mFullScreen).updateFn([this] { setFullScreen(mFullScreen); });

	// set up OSC
	mSender.bind();
#if ! USE_UDP
	mSender.connect();
#endif
}

void LisaFinalApp::mouseDown(MouseEvent event)
{
	//test osc
	osc::Message msg("/hug");
	msg.append("hug");
	mSender.send(msg);
}

void LisaFinalApp::update()
{
}

void LisaFinalApp::draw()
{
	const gl::ScopedViewport scopedViewport(ivec2(0), getWindowSize());
	const gl::ScopedMatrices scopedMatrices;
	const gl::ScopedBlendAlpha scopedBlendAlpha;
	gl::setMatricesWindow(getWindowSize());
	gl::clear();
	gl::color(ColorAf::white());
	gl::disableDepthRead();
	gl::disableDepthWrite();

	if (mChannelDepth && mDrawBackground) {
		gl::enable(GL_TEXTURE_2D);
		const gl::TextureRef tex = gl::Texture::create(*Kinect2::channel16To8(mChannelDepth));
		gl::draw(tex, tex->getBounds(), Rectf(getWindowBounds()));
	}

	if (mChannelBodyIndex) {
		gl::enable(GL_TEXTURE_2D);

		auto drawHand = [&](const Kinect2::Body::Hand& hand, const ivec2& pos) -> void
		{
			switch (hand.getState()) {
			case HandState_Closed:
				gl::color(ColorAf(1.0f, 0.0f, 0.0f, 0.5f));
				break;
			case HandState_Lasso:
				gl::color(ColorAf(0.0f, 0.0f, 1.0f, 0.5f));
				break;
			case HandState_Open:
				gl::color(ColorAf(0.0f, 1.0f, 0.0f, 0.5f));
				break;
			default:
				gl::color(ColorAf(0.0f, 0.0f, 0.0f, 0.0f));
				break;
			}
			gl::drawSolidCircle(pos, 30.0f, 32);
		};

		gl::pushMatrices();
		gl::scale(vec2(getWindowSize()) / vec2(mChannelBodyIndex->getSize()));
		gl::disable(GL_TEXTURE_2D);
		int counter = 0;
		for (const Kinect2::Body &body : mBodyFrame.getBodies()) {
			if (body.isTracked()) {
				gl::color(ColorAf::white());

				auto map = body.getJointMap();

				if (counter == 0) {
					numA1 = (map.at(JointType_Head).getPosition() + map.at(JointType_SpineShoulder).getPosition()) / vec3(2);
					numA2 = (map.at(JointType_ShoulderRight).getPosition() + map.at(JointType_ElbowRight).getPosition() + map.at(JointType_WristRight).getPosition() + map.at(JointType_HandRight).getPosition()) / vec3(4);
					numA3 = (map.at(JointType_ShoulderLeft).getPosition() + map.at(JointType_ElbowLeft).getPosition() + map.at(JointType_WristLeft).getPosition() + map.at(JointType_HandLeft).getPosition()) / vec3(4);
					numA4 = (map.at(JointType_HipRight).getPosition() + map.at(JointType_KneeRight).getPosition() + map.at(JointType_AnkleRight).getPosition() + map.at(JointType_FootRight).getPosition()) / vec3(4);
					numA5 = (map.at(JointType_HipLeft).getPosition() + map.at(JointType_KneeLeft).getPosition() + map.at(JointType_AnkleLeft).getPosition() + map.at(JointType_FootLeft).getPosition()) / vec3(4);
				}

				if (counter == 1) {
					numB1 = (map.at(JointType_Head).getPosition() + map.at(JointType_SpineShoulder).getPosition()) / vec3(2);
					numB2 = (map.at(JointType_ShoulderRight).getPosition() + map.at(JointType_ElbowRight).getPosition() + map.at(JointType_WristRight).getPosition() + map.at(JointType_HandRight).getPosition()) / vec3(4);
					numB3 = (map.at(JointType_ShoulderLeft).getPosition() + map.at(JointType_ElbowLeft).getPosition() + map.at(JointType_WristLeft).getPosition() + map.at(JointType_HandLeft).getPosition()) / vec3(4);
					numB4 = (map.at(JointType_HipRight).getPosition() + map.at(JointType_KneeRight).getPosition() + map.at(JointType_AnkleRight).getPosition() + map.at(JointType_FootRight).getPosition()) / vec3(4);
					numB5 = (map.at(JointType_HipLeft).getPosition() + map.at(JointType_KneeLeft).getPosition() + map.at(JointType_AnkleLeft).getPosition() + map.at(JointType_FootLeft).getPosition()) / vec3(4);

					// calculate distances
					dist1 = sqrt(math<float>::pow(numA1.x - numB1.x, 2) + math<float>::pow(numA1.y - numB1.y, 2) + math<float>::pow(numA1.z - numB1.z, 2));
					dist2 = sqrt(math<float>::pow(numA2.x - numB2.x, 2) + math<float>::pow(numA2.y - numB2.y, 2) + math<float>::pow(numA2.z - numB2.z, 2));
					dist3 = sqrt(math<float>::pow(numA3.x - numB3.x, 2) + math<float>::pow(numA3.y - numB3.y, 2) + math<float>::pow(numA3.z - numB3.z, 2));
					dist4 = sqrt(math<float>::pow(numA4.x - numB4.x, 2) + math<float>::pow(numA4.y - numB4.y, 2) + math<float>::pow(numA4.z - numB4.z, 2));
					dist5 = sqrt(math<float>::pow(numA5.x - numB5.x, 2) + math<float>::pow(numA5.y - numB5.y, 2) + math<float>::pow(numA5.z - numB5.z, 2));
				}

				for (const auto& joint : map) {
					//	console() << joint.first << endl;
					if (joint.second.getTrackingState() == TrackingState::TrackingState_Tracked) {
						vec2 pos(mDevice->mapCameraToDepth(joint.second.getPosition()));
						if (mDrawSkeleton) {
							gl::drawSolidCircle(pos, 5.0f, 32);
							vec2 parent(mDevice->mapCameraToDepth(map.at(joint.second.getParentJoint()).getPosition()));
							gl::drawLine(pos, parent);
						}
					}
				}
				if (mDrawPentagon) {
					// calculate positions which we will use to calculate the five vertices of the pentagons
					vec2 headPos(mDevice->mapCameraToDepth(map.at(JointType_Head).getPosition()));
					vec2 shoulderPos(mDevice->mapCameraToDepth(map.at(JointType_SpineShoulder).getPosition()));

					vec2 shoulderRPos(mDevice->mapCameraToDepth(map.at(JointType_ShoulderRight).getPosition()));
					vec2 elbowRPos(mDevice->mapCameraToDepth(map.at(JointType_ElbowRight).getPosition()));
					vec2 wristRPos(mDevice->mapCameraToDepth(map.at(JointType_WristRight).getPosition()));
					vec2 handRPos(mDevice->mapCameraToDepth(map.at(JointType_HandRight).getPosition()));

					vec2 shoulderLPos(mDevice->mapCameraToDepth(map.at(JointType_ShoulderLeft).getPosition()));
					vec2 elbowLPos(mDevice->mapCameraToDepth(map.at(JointType_ElbowLeft).getPosition()));
					vec2 wristLPos(mDevice->mapCameraToDepth(map.at(JointType_WristLeft).getPosition()));
					vec2 handLPos(mDevice->mapCameraToDepth(map.at(JointType_HandLeft).getPosition()));

					vec2 hipRPos(mDevice->mapCameraToDepth(map.at(JointType_HipRight).getPosition()));
					vec2 kneeRPos(mDevice->mapCameraToDepth(map.at(JointType_KneeRight).getPosition()));
					vec2 ankleRPos(mDevice->mapCameraToDepth(map.at(JointType_AnkleRight).getPosition()));
					vec2 footRPos(mDevice->mapCameraToDepth(map.at(JointType_FootRight).getPosition()));

					vec2 hipLPos(mDevice->mapCameraToDepth(map.at(JointType_HipLeft).getPosition()));
					vec2 kneeLPos(mDevice->mapCameraToDepth(map.at(JointType_KneeLeft).getPosition()));
					vec2 ankleLPos(mDevice->mapCameraToDepth(map.at(JointType_AnkleLeft).getPosition()));
					vec2 footLPos(mDevice->mapCameraToDepth(map.at(JointType_FootLeft).getPosition()));

					gl::lineWidth(5.0f);

					// draw pentagon for 1st person
					if (counter == 0) {
						gl::color(1, 0, 0);

						pointA1 = (headPos + shoulderPos) / vec2(2);
						gl::drawSolidCircle(pointA1, 5.0f, 32);


						pointA2 = (shoulderRPos + elbowRPos + wristRPos + handRPos) / vec2(4);
						gl::drawSolidCircle(pointA2, 5.0f, 32);


						pointA3 = (shoulderLPos + elbowLPos + wristLPos + handLPos) / vec2(4);
						gl::drawSolidCircle(pointA3, 5.0f, 32);

						pointA4 = (hipRPos + kneeRPos + ankleRPos + footRPos) / vec2(4);
						gl::drawSolidCircle(pointA4, 5.0f, 32);

						pointA5 = (hipLPos + kneeLPos + ankleLPos + footLPos) / vec2(4);
						gl::drawSolidCircle(pointA5, 5.0f, 32);

						gl::drawLine(pointA1, pointA2);
						gl::drawLine(pointA2, pointA4);
						gl::drawLine(pointA4, pointA5);
						gl::drawLine(pointA5, pointA3);
						gl::drawLine(pointA3, pointA1);
					}
					// draw pentagon for 2nd person
					else if (counter == 1) {
						gl::color(0, 1, 0);

						pointB1 = (headPos + shoulderPos) / vec2(2);
						gl::drawSolidCircle(pointB1, 5.0f, 32);


						pointB2 = (shoulderRPos + elbowRPos + wristRPos + handRPos) / vec2(4);
						gl::drawSolidCircle(pointB2, 5.0f, 32);


						pointB3 = (shoulderLPos + elbowLPos + wristLPos + handLPos) / vec2(4);
						gl::drawSolidCircle(pointB3, 5.0f, 32);

						pointB4 = (hipRPos + kneeRPos + ankleRPos + footRPos) / vec2(4);
						gl::drawSolidCircle(pointB4, 5.0f, 32);

						pointB5 = (hipLPos + kneeLPos + ankleLPos + footLPos) / vec2(4);
						gl::drawSolidCircle(pointB5, 5.0f, 32);

						gl::drawLine(pointB1, pointB2);
						gl::drawLine(pointB2, pointB4);
						gl::drawLine(pointB4, pointB5);
						gl::drawLine(pointB5, pointB3);
						gl::drawLine(pointB3, pointB1);
					}
				}
				drawHand(body.getHandLeft(), mDevice->mapCameraToDepth(body.getJointMap().at(JointType_HandLeft).getPosition()));
				drawHand(body.getHandRight(), mDevice->mapCameraToDepth(body.getJointMap().at(JointType_HandRight).getPosition()));

				counter++;
			}
		}
	}

	// draw parameters interface
	mParams->draw();
}

void LisaFinalApp::shutdown() {
	mDevice->stop();
}

CINDER_APP(LisaFinalApp, RendererGl)
