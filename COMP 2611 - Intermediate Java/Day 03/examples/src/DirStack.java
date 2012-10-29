import java.io.*;
import java.util.*;

public class DirStack {

	public static void main(String[] args) {
		Stack<File> directoryStack = new Stack<File>();
		File root = new File(File.separator + ".");
		directoryStack.push(root);
		while (directoryStack.size() > 0) {
			File currentDirectory = directoryStack.pop();
			System.out.println(currentDirectory);
			String[] subdirectories = currentDirectory.list();
			if (subdirectories != null) {
				for (int i = 0; i < subdirectories.length; i++) {
					try {
						String fname = currentDirectory.getCanonicalPath()
								+ File.separator + subdirectories[i];
						File f = new File(fname);

						if (f.isDirectory())
							directoryStack.push(f);
					} catch (IOException e) {
						System.out.println(e);
					}
				}
			}
		}
	}
}
