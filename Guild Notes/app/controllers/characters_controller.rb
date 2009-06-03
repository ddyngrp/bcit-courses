class CharactersController < ApplicationController
  def index
    @person = Person.find(params[:person_id])
    @characters = @person.characters
  end

  def show
    @person = Person.find(params[:person_id])
    @character = @person.characters.find(params[:id])
  end

  def new
    @person = Person.find(params[:person_id])
    @character = @person.characters.build
  end
  
  def create
    @person = Person.find(params[:person_id])
    @character = @person.characters.build(params[:character])
    if @character.save
      redirect_to person_character_url(@person, @character)
    else
      render :action => "new"
    end
  end

  def edit
    @person = Person.find(params[:person_id])
    @character = @person.characters.find(params[:id])
  end

  def update
    @person = Person.find(params[:person_id])
    @character = Character.find(params[:id])
    if @character.update_attributes(params[:character])
      redirect_to person_character_url(@person, @character)
    else
      render :action => "edit"
    end
  end

  def destroy
    @person = Person.find(params[:person_id])
    @character = Character.find(params[:id])
    @character.destroy

    respond_to do |format|
      format.html { redirect_to person_characters_path(@person) }
      format.xml  { head :ok }
    end
  end

end
