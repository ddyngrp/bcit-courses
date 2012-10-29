package MVCTest.ui;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.util.Iterator;
import java.util.Observable;
import java.util.Observer;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import MVCTest.data.Colors;
import MVCTest.data.NamedColor;

public class MainFrame extends JFrame {

	private ColorsModel colorsModel;
	private ColorsController colorsController;
	private JList colorsView;
	private JLabel colorSwatch;
	private JLabel colorText;

	public MainFrame() {
		super("ColorsMVCTest");

		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setSize(400, 300);
		setLocationRelativeTo(null);

		create();
	}

	private void create() {
		// create the list
		colorsModel = new ColorsModel();
		colorsController = new ColorsController();
		colorsView = new JList(colorsModel);
		ListSelectionModel listSelectionModel = colorsView.getSelectionModel();
		listSelectionModel.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		colorsView.addListSelectionListener(colorsController);
        JScrollPane colorsScrollPane = new JScrollPane(colorsView);
        colorsScrollPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        colorsScrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        colorsScrollPane.setPreferredSize(new Dimension(150, 20));
        add(colorsScrollPane, BorderLayout.WEST);
        
        // create the details view
        JPanel detailsView = new JPanel();
        add(detailsView, BorderLayout.CENTER);
        detailsView.setLayout(new GridLayout(0,1));
        
        colorSwatch = new JLabel();
        colorSwatch.setOpaque(true);
        detailsView.add(colorSwatch);
        
        colorText = new JLabel();
        detailsView.add(colorText);
	}

	// Inner classes ---------------------------------------------------------

	public class ColorItem {

		private NamedColor color;

		ColorItem(NamedColor color) {
			this.color = color;
		}

		/**
		 * @return Returns the color.
		 */
		public NamedColor getColor() {
			return color;
		}

		public String toString() {
			return color.getName();
		}
	}
	
	private class ColorsModel extends DefaultListModel {

		ColorsModel() {
			Iterator iterator = Colors.getTheInstance().getIterator();
			while (iterator.hasNext()) {
				NamedColor color = (NamedColor) iterator.next();
				// call DefaultListModel addElement(...)
				addElement(new ColorItem(color));
			}
		}
	}

	private class ColorsController implements ListSelectionListener, Observer {

		public void valueChanged(ListSelectionEvent event) {
		    if (event.getValueIsAdjusting()) {
		        return;
		    }

			System.out.println(event);

			Object o = colorsView.getSelectedValue();
			if (o == null) {
				return;
			}
			
		    ColorItem item = (ColorItem) o;
			System.out.println(item);
			
			colorSwatch.setBackground(item.getColor().getColor());
			colorText.setText(item.getColor().toString());
		}
		

		public void update(Observable arg0, Object arg1) {
			// TODO Auto-generated method stub
			
		}

	}

}
