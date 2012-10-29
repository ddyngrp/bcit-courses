
/**
 * Hash generator.
 */

import net.rim.device.api.crypto.*;
import java.io.IOException;

public class Hash {
	
	/**
	 * Blank Key Shortcut.
	 */
	public static String hash(String plainText) throws CryptoException, IOException {
		String key = "";
		return hash(plainText, key);
	}
	
	/**
	 * Generates an SHA1 hash given input and a key.
	 */
	public static String hash(String plainText, String hashKey) throws CryptoException, IOException {
		// temporary output storage
    	byte[] digestData = {};
    	
    	// generate hash
    	HMACKey key = new HMACKey(hashKey.getBytes());
    	HMAC hMac = new HMAC(key, new SHA1Digest());
    	MACOutputStream macStream = new MACOutputStream(hMac, null);
    	macStream.write(plainText.getBytes());
    	hMac.getMAC(digestData, 0);
    	
    	// return hash
    	return new String(digestData);
	}
}