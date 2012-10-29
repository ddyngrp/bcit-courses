/*
 * Hash.java
 *
 * MLogger, 2008
 * Confidential and proprietary.
 */
package src;
import net.rim.device.api.crypto.*;
import java.io.IOException;

public class Hash {
        
        /**
         * Generates an SHA1 hash given an input (uses a blank key).
         */
        public static String hash(String plainText) {
                String key = "";
                return hash(plainText, key);
        }
        
        /**
         * Generates an SHA1 hash given input and a key.
         */
        public static String hash(String plainText, String hashKey) {
            // temporary output storage
            byte[] digestData = {};
            
            // generate hash
            try {
                HMACKey key = new HMACKey(hashKey.getBytes());
                HMAC hMac = new HMAC(key, new SHA1Digest());
                MACOutputStream macStream = new MACOutputStream(hMac, null);
                macStream.write(plainText.getBytes());
                hMac.getMAC(digestData, 0);
            } catch (CryptoException e) {
                System.out.println("Crypt Exception: " + e);
                return "BAD Crypto";
            } catch (IOException e) {
                System.out.println("IOException: " + e);
                return "BAD IO";
            }
            
            // return hash
            return new String(digestData);
        }
}
