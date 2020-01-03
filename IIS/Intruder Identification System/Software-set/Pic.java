import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.highgui.Highgui;
import org.opencv.highgui.VideoCapture;

public class Pic {

    public static void main (String args[]){

    	System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
    	Mat frame = new Mat();
    	VideoCapture camera = new VideoCapture(0);
    
    
    
    	int i=0;
    	
    	//i=Integer.parseInt(args[0]);
    	while(true){
    		
    		
    		try {
    	        Thread.sleep(10000);                 //1000 milliseconds is one second.
    	    } catch(InterruptedException ex) {
    	        Thread.currentThread().interrupt();
    	    }
    		camera.open(0);
    		camera.read(frame);
    		camera.release();
    		Highgui.imwrite("C:\\Users\\username\\cloud_account\\subfolder\\filename"+i+".jpg", frame);
    		i++;
    		i=i%50;
    	}
    
    }
}