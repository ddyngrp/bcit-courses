import net.rim.device.api.ui.UiApplication;
import net.rim.device.api.ui.component.*;
import net.rim.device.api.ui.Field;
import net.rim.device.api.ui.container.*;
import net.rim.device.api.ui.MenuItem;
import javax.microedition.media.*;
import javax.microedition.media.control.*;
import net.rim.device.api.system.Bitmap;


public class SnapShotAPI extends UiApplication {

	private MainScreen home, preview;
	private EditField logField;
	ObjectChoiceField qualityField;
	private VideoControl vc;
	private String encoding;
	private Player p;
	private Field viewFinder;
	private BitmapField bitmapField;
	private boolean isViewfinderVisible;
	private MenuItem mi = new MenuItem("Viewfinder", 1, 1) {
		public void run() {			
			try {
				setupEncoding();
				logField.setText("");
				log("Active Encoding: "+encoding);
				if(vc!=null){					
					UiApplication.getUiApplication().invokeLater(new Runnable(){
						public void run(){	
							if(home.getFieldCount()<3){								
								home.delete(logField);
								home.add(viewFinder);								
								home.add(logField);
								viewFinder.setFocus();
							}
														
						}
					});				
					vc.setVisible(true);			
					isViewfinderVisible=true;
					log("Initialized ViewFinder");								
				}else {
					log("VideoControl not initialized");
				}
					
			} catch (Throwable e) {
				log(e + ":" + e.getMessage());
			}				
		}
	};
	private MenuItem mi1 = new MenuItem("Snap", 1, 1) {
		public void run() {			
			try {
				logField.setText("");
				log("Taking snapshot");
				if(vc!=null && isViewfinderVisible){	
					String imageType = "encoding=jpeg&width=640&height=480&quality=superfine";
					final byte[] imageBytes = vc.getSnapshot(encoding);
					log("Encoding: "+encoding);
					log("Size: " + imageBytes.length);
					UiApplication.getUiApplication().invokeLater(new Runnable(){
						public void run(){
							if (imageBytes.length>0 && Dialog.ask(Dialog.D_YES_NO, "Draw image?")==Dialog.YES){								
								Bitmap image = Bitmap.createBitmapFromBytes(imageBytes, 0, imageBytes.length, 4);
								bitmapField.setBitmap(image);
								bitmapField.setSpace(5, 5);								
								pushScreen(preview);
								log("Image Drawn!");								
							}
						}
					});										
				} else 
					log("Viewfinder not visible!");	
				
				if(isViewfinderVisible){
					home.delete(viewFinder);				
					isViewfinderVisible=false;
				}
			} catch(Throwable e){
				log(e + ":" + e.getMessage());
			}
		}
	};
	private MenuItem mi2 = new MenuItem("FullScreen", 1, 1) {
		public void run() {			
			if(vc!=null){
				try {					
					vc.setDisplayFullScreen(true);
				} catch (MediaException e) {
					log(e.getMessage());
				}
			} else log("VideoControl is not initialized");
		}
	};
	
	private MenuItem mi3 = new MenuItem("Exit FullScreen", 1, 1) {
		public void run() {			
			if(vc!=null){
				try {					
					vc.setDisplayFullScreen(false);
				} catch (MediaException e) {
					log(e.getMessage());
				}
			} else log("VideoControl is not initialized");
		}
	};

	public static void main(String[] args) {
		SnapShotAPI app = new SnapShotAPI();
		app.enterEventDispatcher();
	} 

	public SnapShotAPI(){		
		home = new MainScreen();		
		logField = new EditField("Log:","");
		bitmapField = new BitmapField();
		String[] choices = {"SuperFine 1600x1200", "Fine 1600x1200", "Normal 1600x1200", "SuperFine 1024x768", "Fine 1024x768", "Normal 1024x768", "SuperFine 640x480", "Fine 640x480", "Normal 640x480"};    
		qualityField = new ObjectChoiceField("Quality", choices);
		home.add(qualityField);
		home.add(logField);		
		home.addMenuItem(mi);
		home.addMenuItem(mi1);
		home.addMenuItem(mi2);
		home.addMenuItem(mi3);
		preview = new MainScreen();
		preview.add(bitmapField);	
		
		pushScreen(home);
		try{						
			p = Manager.createPlayer("capture://video");						
			p.realize();
			log("Player realized");
			p.prefetch();
			log("Player prefetched");
			p.start();
			log("Player started");				
			vc = (VideoControl) p.getControl("VideoControl");
			viewFinder = (Field)vc.initDisplayMode(VideoControl.USE_GUI_PRIMITIVE, "net.rim.device.api.ui.Field");
			log("Initialized.");
		} catch (Exception me){
			log(me.getMessage());
		}
		isViewfinderVisible=false;
	}
	
	private void setupEncoding(){
		switch (qualityField.getSelectedIndex()){
			case 0:
				encoding = "encoding=jpeg&width=1600&height=1200&quality=superfine";
				break;
			case 1:
				encoding = "encoding=jpeg&width=1600&height=1200&quality=fine";
				break;
			case 2:
				encoding = "encoding=jpeg&width=1600&height=1200&quality=normal";
				break;
			case 3:
				encoding = "encoding=jpeg&width=1024&height=768&quality=superfine";
				break;
			case 4:
				encoding = "encoding=jpeg&width=1024&height=768&quality=fine";
				break;
			case 5:
				encoding = "encoding=jpeg&width=1024&height=768&quality=normal";
				break;
			case 6:
				encoding = "encoding=jpeg&width=640&height=480&quality=superfine";
				break;
			case 7:
				encoding = "encoding=jpeg&width=640&height=480&quality=fine";
				break;
			case 8:
				encoding = "encoding=jpeg&width=640&height=480&quality=normal";
				break;
			default:
				encoding = "encoding=jpeg&width=640&height=480&quality=superfine";	
			
		}
	}
	private void log(final String msg) {
		UiApplication.getUiApplication().invokeLater(new Runnable() {
			public void run() {
				logField.setText(logField.getText() + "\n" + msg);
			}
		});
	}
	
}
