class camerascreen {
    open a video stream
    createCameraGUI()
    
    if "Snap" pressed
        capture current frame
        switch to Image screen
    if "Cancel" pressed
        switch to Application screen
}

class imagescreen {
    createImageGUI()
    present bitmap of caught frame
    if "Save" pressed
        Add a new Image that takes that caught frame to the MediaController
        Return back to the Camera screen
    if "Cancel" pressed
        Return back to Camera screen
}


createCameraGUI {
    create video stream //camera preview
    create "Snap" button
    create "Cancel" button
}

createImageGUI {
    convert caught frame into bitmap
    present bitmap on screen
    create "Save" button
    create "Cancel" button
}