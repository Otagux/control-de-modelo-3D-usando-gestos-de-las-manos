#include "hand_detector.h"
#include "/home/otagux/mediapipe/mediapipe/framework/formats/image_frame.h"

#include <mediapipe/framework/calculator_graph.h>
#include <mediapipe/framework/formats/landmark.pb.h>
#include <mediapipe/framework/formats/image_frame.h>
#include <mediapipe/framework/port/parse_text_proto.h>
#include <mediapipe/framework/port/status.h>

#include <opencv2/imgproc.hpp>

using namespace mediapipe;

CalculatorGraph graph;
std::unique_ptr<OutputStreamPoller> poller;

HandDetector::HandDetector() {

    initialized = false;

    std::string graphConfig = R"pb(
        input_stream: "input_video"
        output_stream: "landmarks"

        node {
          calculator: "HandLandmarkTrackingCpu"
          input_stream: "IMAGE:input_video"
          output_stream: "LANDMARKS:landmarks"
        }
    )pb";

    CalculatorGraphConfig config =
        ParseTextProtoOrDie<CalculatorGraphConfig>(graphConfig);

    graph.Initialize(config);

    poller = std::make_unique<OutputStreamPoller>(
        graph.AddOutputStreamPoller("landmarks").value()
    );

    graph.StartRun({});
    initialized = true;
}

std::vector<Landmark> HandDetector::detect(const cv::Mat& frame) {

    std::vector<Landmark> result;

    if (!initialized)
        return result;

    auto input_frame = absl::make_unique<ImageFrame>(
        ImageFormat::SRGB,
        frame.cols,
        frame.rows,
        ImageFrame::kDefaultAlignmentBoundary
    );

    cv::Mat frame_copy;
    cv::cvtColor(frame, frame_copy, cv::COLOR_BGR2RGB);

    std::memcpy(
        input_frame->MutablePixelData(),
        frame_copy.data,
        frame_copy.total() * frame_copy.elemSize()
    );

    size_t frame_timestamp =
        (double)cv::getTickCount() / cv::getTickFrequency() * 1e6;

    graph.AddPacketToInputStream(
        "input_video",
        Adopt(input_frame.release()).At(Timestamp(frame_timestamp))
    );

    Packet packet;

    if (poller->Next(&packet)) {

        auto& landmarks =
            packet.Get<NormalizedLandmarkList>();

        for (int i = 0; i < landmarks.landmark_size(); i++) {

            Landmark p;

            p.x = landmarks.landmark(i).x();
            p.y = landmarks.landmark(i).y();
            p.z = landmarks.landmark(i).z();

            result.push_back(p);
        }
    }

    return result;
}

