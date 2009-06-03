class CreateCharacters < ActiveRecord::Migration
  def self.up
    create_table :characters do |t|
      t.string :name
      t.string :char_class
      t.text :notes
      t.references :person

      t.timestamps
    end
  end

  def self.down
    drop_table :characters
  end
end
