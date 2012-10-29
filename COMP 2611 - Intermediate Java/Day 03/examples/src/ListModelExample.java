import java.util.*;
import javax.swing.*;
import java.awt.*;

public class ListModelExample extends JFrame {

	private static final Random random = new Random();

	private JList list;

	private MyListModel listData;

	public static void main(String[] args) {
		new ListModelExample();
	}

	public ListModelExample() {
		create();

		load();

		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setSize(400, 300);
		setLocationRelativeTo(null);
		setVisible(true);
	}

	private void create() {
		list = new JList();
		getContentPane().add(new JScrollPane(list), BorderLayout.CENTER);
	}

	private void load() {
		Vector<MyItem> items = new Vector<MyItem>();
		items.add(new MyItem());
		items.add(new MyItem());
		items.add(new MyItem());
		items.add(new MyItem());
		items.add(new MyItem());

		listData = new MyListModel(items);

		list.setModel(listData);
	}

	class MyItem {
		public String getShortDescription() {
			return random.nextInt(10) + " conditions apply.";
		}
	}

	class MyListModel extends AbstractListModel {

		private Vector<MyItem> data;

		public MyListModel(Vector<MyItem> data) {
			setData(data);
		}

		public void setData(Vector<MyItem> data) {
			this.data = data;
		}

		public int getSize() {
			if (data == null) {
				return 0;
			}
			int size = data.size();
			return size;
		}

		public Object getElementAt(int index) {
			MyItem item = data.get(index);
			return item.getShortDescription();
		}
	}
}
