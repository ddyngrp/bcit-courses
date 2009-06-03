class Person < ActiveRecord::Base
  validates_presence_of :name
  validates_length_of :name, :minimum => 3
  validates_numericality_of :time_zone, :allow_nil => true
  has_many :characters
end
