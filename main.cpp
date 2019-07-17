//*******************************************
//*Fun withC++ / OpenCv frame handling for  *
//*video                                     *
//*******************************************

//*******************************************
//*                Directives               *
//*******************************************
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//*******************************************
//*                CONSTANTS                *
//*******************************************
const string VIDEO_FILE =
"/Users/michaelgamble/Movies/Sample_Videos/endgame.mp4";
string ORIGINAL_VIDEO =
"Original";


//*******************************************
//*           Function Prototypes           *
//*******************************************



int main(int argc, char** argv)
{

    VideoCapture cap(argv[1]);               //Create a video capture object
    
    if(!cap.isOpened())                         //If capture device didn't open
    {
        cerr  <<  "Error: Video capture object failed to open."  <<  endl;
        cerr  <<  "Make sure the file name is correct, the camera is available \t";
        cerr  <<  "or that you have all necessary codecs installed and run this \t";
        cerr  <<  "program again."  <<  endl  <<  endl;
        
        cerr  <<  "Program terminated, good-bye!"  <<  endl;
        
        return -1;                              //Quit
    }
    
    double fps = cap.get(CAP_PROP_FPS);         //Get the FPS
    Size frameSize(                             //Get the input frame size - width x height
                   static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH)),
                   static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT))
                   );
    double fourcc = cap.get(CAP_PROP_FOURCC);   //Get the codec
    
    cout  <<  "FPS: "  <<  fps  <<  endl;       //Print the video speed in fps
    cout  <<  "Frame Size: "                    //Print the frame size
          <<  "width = "    << frameSize.width
          <<  " height = "  << frameSize.height
          <<  endl;
    

    
    
    
    VideoWriter writer(                         //Create a VideoWriter object
                "Output.mp4",                   //Output file name
                fourcc,                         //Code for out file
                fps,                            //Playback speed
                frameSize,                      //Size of frames w x h
                true  );                        //isColor? t or f
    
    if(!writer.isOpened())                      //If writer object didn't open
    {
        cerr  <<  "Error: Video writer object failed to open."  <<  endl;
        cerr  <<  "Make sure you have writer privleges to the output director \t";
        cerr  <<  "and all necessary codecs installed and run this program again."
              <<  endl  <<  endl;
        
        cerr  <<  "Program terminated, good-bye!"  <<  endl;
        
        return -1;                              //Quit
    }
    
    
    Mat frames;                                 //Create Mat object to hold the
                                                //frames
    
    namedWindow(ORIGINAL_VIDEO,                 //Window to host output
                WINDOW_AUTOSIZE);               //Auto size the window
    
    
    while(true)
    {
        cap  >> frames;                         //Read the frame to the array
        
        if(frames.empty())                      //Test for empty frame
        { break; }                              //Break the loop
        
        writer.write(frames);                   //Write the frame
        
        imshow(ORIGINAL_VIDEO, frames);         //Display the frame
        
        char c = waitKey(fps);                  //Next frame
        if(c == 27)                             //or quit [esc]
        { break; }                              //Break the loop
        
    }
    
    cout  <<  "End of video."  <<  endl  <<  endl;
    
    
    cap.release();                              //Release the caputre 
    
    return 0;
    
}
