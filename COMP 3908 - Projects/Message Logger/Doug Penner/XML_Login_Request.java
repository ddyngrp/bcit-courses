public class XML_Login_Request implements XML_Request {
        
        protected static final String hashKey = "";
        
        protected String username;
        protected String password;
        
        /**
         * Constructor for creating a login request.
         * @param username Username (plaintext)
         * @param password Password (plaintext)
         */
        XML_Login_Request(String username, String password){
                this.username = username;
                // TODO: Fix Hash Function!
                // this.password = Hash.hash(password, hashkey);
                this.password = password;
        }
        
        public String toString() {
                /*
                try {
                        password = Hash.hash(password);
                } catch (IOException e) {
                        throw new CryptoException(e.toString());
                }
                */
                return "<?xml version=\"1.0\" encoding=\"utf-8\"?>" +
                "<soap:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">" +
                "       <soap:Body>" +
                "       <ValidateUser xmlns=\"http://virus-box/MLogger\">" +
                "               <userName>" + username + "</userName>" +
                "               <password>" + password + "</password>" +
                "       </ValidateUser>" +
                "       </soap:Body>" +
                "</soap:Envelope>";
        }
        
}
