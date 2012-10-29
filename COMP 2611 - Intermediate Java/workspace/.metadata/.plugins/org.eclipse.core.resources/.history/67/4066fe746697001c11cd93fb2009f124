package a00123456.bedz.data;

/**
 * © Copyright 2007 Eastman Kodak Company. All rights reserved.
 * User: scirka
 * Date: 29-Oct-2007
 * Time: 10:25:45 PM
 */
public enum Province {
	ALBERTA("AB", "Alberta"),
	BRITISH_COLUMBIA("BC", "British Columbia"),
	MANITOBA("MB", "Manitoba"),
	NEW_BRUNSWICK("NB", "New Brunswick"),
	NEWFOUNDLAND_AND_LABRADOR("NL", "Newfoundland and Labrador"),
	NUNAVUT("NU", "Nunavut"),
	NORTHWEST_TERRITORIES("NT", "Northwest Territories"),
	NOVA_SCOTIA("NS", "Nova Scotia"),
	ONTARIO("ON", "Ontario"),
	PRINCE_EDWARD_ISLAND("PE", "Prince Edward Island"),
	QUEBEC("QC", "Quebec"),
	SASKATCHEWAN("SK", "Saskatchewan"),
	YUKON_TERRITORY("YT", "Yukon Territory");

	private String initials;
	private String name;

	Province(String intials, String name) {
		this.initials = intials;
		this.name = name;
	}

	public static Province getProvince(String value) {
		if (value.length() == 2) {
			if (value.equalsIgnoreCase(ALBERTA.initials)) {
				return ALBERTA;
			} else if (value.equalsIgnoreCase(BRITISH_COLUMBIA.initials)) {
				return BRITISH_COLUMBIA;
			} else if (value.equalsIgnoreCase(MANITOBA.initials)) {
				return MANITOBA;
			} else if (value.equalsIgnoreCase(NEW_BRUNSWICK.initials)) {
				return NEW_BRUNSWICK;
			} else if (value.equalsIgnoreCase(NEWFOUNDLAND_AND_LABRADOR.initials)) {
				return NEWFOUNDLAND_AND_LABRADOR;
			} else if (value.equalsIgnoreCase(NUNAVUT.initials)) {
				return NUNAVUT;
			} else if (value.equalsIgnoreCase(NORTHWEST_TERRITORIES.initials)) {
				return NORTHWEST_TERRITORIES;
			} else if (value.equalsIgnoreCase(NOVA_SCOTIA.initials)) {
				return NOVA_SCOTIA;
			} else if (value.equalsIgnoreCase(ONTARIO.initials)) {
				return ONTARIO;
			} else if (value.equalsIgnoreCase(PRINCE_EDWARD_ISLAND.initials)) {
				return PRINCE_EDWARD_ISLAND;
			} else if (value.equalsIgnoreCase(QUEBEC.initials)) {
				return QUEBEC;
			} else if (value.equalsIgnoreCase(SASKATCHEWAN.initials)) {
				return SASKATCHEWAN;
			} else if (value.equalsIgnoreCase(YUKON_TERRITORY.initials)) {
				return YUKON_TERRITORY;
			}
		} else {
			if (value.equalsIgnoreCase(ALBERTA.name)) {
				return ALBERTA;
			} else if (value.equalsIgnoreCase(BRITISH_COLUMBIA.name)) {
				return BRITISH_COLUMBIA;
			} else if (value.equalsIgnoreCase(MANITOBA.name)) {
				return MANITOBA;
			} else if (value.equalsIgnoreCase(NEW_BRUNSWICK.name)) {
				return NEW_BRUNSWICK;
			} else if (value.equalsIgnoreCase(NEWFOUNDLAND_AND_LABRADOR.name)) {
				return NEWFOUNDLAND_AND_LABRADOR;
			} else if (value.equalsIgnoreCase(NUNAVUT.name)) {
				return NUNAVUT;
			} else if (value.equalsIgnoreCase(NORTHWEST_TERRITORIES.name)) {
				return NORTHWEST_TERRITORIES;
			} else if (value.equalsIgnoreCase(NOVA_SCOTIA.name)) {
				return NOVA_SCOTIA;
			} else if (value.equalsIgnoreCase(ONTARIO.name)) {
				return ONTARIO;
			} else if (value.equalsIgnoreCase(PRINCE_EDWARD_ISLAND.name)) {
				return PRINCE_EDWARD_ISLAND;
			} else if (value.equalsIgnoreCase(QUEBEC.name)) {
				return QUEBEC;
			} else if (value.equalsIgnoreCase(SASKATCHEWAN.name)) {
				return SASKATCHEWAN;
			} else if (value.equalsIgnoreCase(YUKON_TERRITORY.name)) {
				return YUKON_TERRITORY;
			}
		}

		return null;
	}

	@Override
	public String toString() {
		return String.format("%s (%s)", name, initials);
	}
}
