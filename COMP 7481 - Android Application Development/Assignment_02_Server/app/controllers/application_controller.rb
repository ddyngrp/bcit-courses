class ApplicationController < ActionController::Base
  helper :all
  protect_from_forgery
  helper_method :detect_browser
  
  private
  MOBILE_BROWSERS = ["android", "ipod", "opera mini", "blackberry", "palm", "hiptop", "avantgo", 
    "plucker", "xiino", "blazer", "elaine", "windows ce; ppc;", "windows ce; smartphone;",
    "windows ce; iemobile", "up.browser", "up.link", "mmp", "symbian", "smartphone", "midp",
    "wap", "vodafone", "o2", "pocket", "kindle", "mobile", "pda", "psp", "treo"]
  
  def authenticate
    authenticate_or_request_with_http_basic do |username, password|
      #true
      username == "android" && password == "android"
    end
  end

  def detect_browser
    agent = request.headers["HTTP_USER_AGENT"].downcase
    MOBILE_BROWSERS.each do |m|
      return "Browsing from a mobile device." if agent.match(m)
    end
    return "Browsing from a desktop machine."
  end
end