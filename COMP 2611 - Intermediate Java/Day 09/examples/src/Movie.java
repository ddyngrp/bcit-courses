import java.io.*;

public class Movie implements Serializable {

	private String category;
	private String title;

	public Movie(String category, String title) {
		this.category = category;
		this.title = title;
	}

	public String toString() {
		return "CATEGORY=" + category + "\t" + "TITLE=" + title;
	}

	public void writeObject(ObjectOutputStream out)
			throws IOException {
		out.writeObject(category);
		out.writeObject(title);
	}

	public void readObject(ObjectInputStream in)
			throws IOException, ClassNotFoundException {
		category = (String) in.readObject();
		title = (String) in.readObject();
	}
}
