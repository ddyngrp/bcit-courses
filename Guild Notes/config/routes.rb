ActionController::Routing::Routes.draw do |map|
  map.resources :people, :has_many => :characters
  map.connect ':controller/:action/:id'
  map.connect ':controller/:action/:id.:format'
  map.root :controller => "home"
end
