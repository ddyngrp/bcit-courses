class Character < ActiveRecord::Base
  belongs_to :person
  #validates_presence_of :name
end
