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
//*               STRUCTURES                *
//*******************************************
struct VidInfo
{
    VideoCapture *cap = nullptr;            //Pointer to the cap object
    double fourcc;                          //Video codec
    double fps;                             //Frame play speed
    Size frameSize;                         //Frame Size w x h
    double runTime;                         //Film run time
};

//*******************************************
//*           Function Prototypes           *
//*******************************************
VideoCapture openCapture();
struct VidInfo getVidInfo(VideoCapture cap);
VideoWriter openWriter(VidInfo video);

int main(int argc, char** argv)
{

    VideoCapture cap(openCapture());            //Create and open the catputre object by
                                                //calling the openCapture() function
    
    VidInfo video = getVidInfo(cap);            //Call the
    
    VideoWriter writer(openWriter(video));
    
    
    
    
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
        
        char c = waitKey(video.fps);            //Next frame > video.fps
        if(c == 27)                             //or quit if [esc]
        { break; }                              //and break the loop
        
    }
    
    //Clean up
    destroyWindow(ORIGINAL_VIDEO);              //Close the window
    cap.release();                              //Release the capture
    
    cout  <<  "End of video."  <<  endl  <<  endl;
    
    
    cap.release();                              //Release the caputre memory
    
    return 0;
    
}

//*******************************************
//*getVidInfo function: accepts a tested and*
//*open capture object and returns a struct *
//*containing the capture object video info *
//*******************************************
struct VidInfo getVidInfo(VideoCapture cap)
{
    VidInfo video;
    
    video.fps = cap.get(CAP_PROP_FPS);          //Get the FPS
    
    //Get the input frame size - width x height
    video.frameSize.width  = (int) cap.get(CAP_PROP_FRAME_WIDTH);
    video.frameSize.height = (int) cap.get(CAP_PROP_FRAME_HEIGHT);
    video.fourcc =  cap.get(CAP_PROP_FOURCC);   //Get the codec
    //Store the run time
    video.runTime = (cap.get(CAP_PROP_FRAME_COUNT) / video.fps);
    video.cap = &cap;                           //Reference to the capture
    
    //Print the video info
    cout  <<  "FPS: "  <<  video.fps  <<  endl; //Print the video speed in fps
    cout  <<  "Frame Size: "                    //Print the frame size
    <<  "width = "    << video.frameSize.width  //frame width
    <<  " height = "  << video.frameSize.height //frame height
    <<  endl;
    cout  <<  "Run Time: "  <<  video.runTime  <<  "s "  <<  endl;
    
    return video;
}


//*******************************************
//*openCapture function: no parameters, test*
//*and open a capture object initalized with*
//*a file                                   *
//*******************************************
VideoCapture openCapture()
{
    VideoCapture cap(VIDEO_FILE);               //Create a video capture object
    
    if(!cap.isOpened())                         //If capture device didn't open
    {
        cerr  <<  "Error: Video capture object failed to open."  <<  endl;
        cerr  <<  "Make sure the file name is correct, the camera is available \n";
        cerr  <<  "or that you have all necessary codecs installed and run this \n";
        cerr  <<  "program again."  <<  endl  <<  endl;
        
        cerr  <<  "Program terminated, good-bye!"  <<  endl;
        
        return -1;                              //Quit
    }
    
    return cap;
}

    
//*******************************************
//*openWriter function: accepts a struct of *
//*VidInfo, opens the writer, and tests the *
//*to see if the writer opened              *
//*******************************************
VideoWriter openWriter(VidInfo video)
{
    VideoWriter writer(                         //Create a VideoWriter object
                       "Output.mp4",            //Output file name
                       video.fourcc,            //Code for out file
                       video.fps,               //Playback speed
                       video.frameSize,         //Size of frames w x h
                       true  );                 //isColor? t or f
    
    if(!writer.isOpened())                      //If writer object didn't open
    {
        cerr  <<  "Error: Video writer object failed to open."  <<  endl;
        cerr  <<  "Make sure you have writer privleges to the output director \n";
        cerr  <<  "and all necessary codecs installed and run this program again."
              <<  endl  <<  endl;
        
        cerr  <<  "Write function terminated, no file written." <<  endl;
        
        EXIT_FAILURE;                           //Quit the function
                                                //The program should still preview
                                                //the file 
    }
    
    return writer;
}
