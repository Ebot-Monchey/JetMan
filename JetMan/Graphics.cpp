// Implements the classes found in graphics.h

#include <string>
#include <stdlib.h>
#include <allegro5/allegro_primitives.h>
#include "graphics.h"
#include "utils.h"

// ========================Rectangle===============================
/*
 * Creates a new rectangle with the given bounds.
 */
JetMan::Graphics::Rectangle::Rectangle(float x, float y, float width, float height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

/*
 * Gets the x coordinate of the rectangle.
 */
float JetMan::Graphics::Rectangle::getX() {
	return x;
}

/*
 * Sets the x coordinate of the rectangle.
 */
void JetMan::Graphics::Rectangle::setX(float x) {
	this->x = x;
}

/*
  * Gets the y coordinate of the rectangle.
*/
float JetMan::Graphics::Rectangle::getY() {
	return y;
}

/*
 * Sets the y coordinate of the rectangle.
 */
void JetMan::Graphics::Rectangle::setY(float y) {
	this->y = y;
}

/*
 * Gets the width of the rectangle.
 */
float JetMan::Graphics::Rectangle::getWidth() {
	return width;
}

/*
 * Sets the width of the rectangle.
 */
void JetMan::Graphics::Rectangle::setWidth(float width) {
	this->width = width;
}

/*
 * Gets the height of the rectangle.
 */
float JetMan::Graphics::Rectangle::getHeight() {
	return height;
}

/*
 * Sets the height of the rectangle.
 */
void JetMan::Graphics::Rectangle::setHeight(float height) {
	this->height = height;
}

/*
 * Sets the bounds of the rectangle.
 */
void JetMan::Graphics::Rectangle::setBounds(float x, float y, float width, float height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

/*
 * Determines whether the rectangle intersects another rectangle.
 */
bool JetMan::Graphics::Rectangle::intersects(JetMan::Graphics::Rectangle rect) {
	if (rect.getX() > x + width) {
		return false;
	}
	else if (rect.getX() + rect.getWidth() < x) {
		return false;
	}
	else if (rect.getY() > y + height) {
		return false;
	}
	else if (rect.getY() + rect.getHeight() < y) {
		return false;
	}
	else {
		return true;
	}
}

// ===================================Displayable=======================================
/*
 * Gets the bounding rectangle of the displayable object.
 */
JetMan::Graphics::Rectangle JetMan::Graphics::Displayable::getBounds() {
	return bounds;
}

/*
 * Sets the position of the displayable object.
 */
void JetMan::Graphics::Displayable::setPosition(float x, float y) {
	JetMan::Graphics::Rectangle rect = getBounds();
	rect.setX(x);
	rect.setY(y);
	setBounds(rect);
}

/*
 * Sets the bounding rectangle of the displayable object.
 */
void JetMan::Graphics::Displayable::setBounds(JetMan::Graphics::Rectangle bounds) {
	this->bounds = bounds;
}

// ===============================Panel================================================
/*
 * Adds the widget to the panel.
 */
void JetMan::Graphics::Panel::addWidget(JetMan::Graphics::Panel::Widget* widget) {
	JetMan::Graphics::Rectangle panelBounds = getBounds();
	JetMan::Graphics::Rectangle widgetBounds = widget->getBounds();
	widgetBounds.setBounds(widgetBounds.getX() + panelBounds.getX(), widgetBounds.getY() + panelBounds.getY(), widgetBounds.getWidth(), widgetBounds.getHeight());
	widgets.push_back(widget);
}

/*
 * Draws the panel by drawing all its children widgets.
 */
void JetMan::Graphics::Panel::draw() {
	int x, y, width, height;
	al_get_clipping_rectangle(&x, &y, &width, &height);
	JetMan::Graphics::Rectangle bounds = getBounds();
	al_set_clipping_rectangle(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight());
	for (Widget* w : widgets) {
		w->draw();
	}
	al_set_clipping_rectangle(x, y, width, height);
}

/*
 * Called when the mouse is hovering over the widget.
 */
JetMan::Graphics::Widget* JetMan::Graphics::Panel::onMouseOver(JetMan::Graphics::Rectangle mouse) {
	for (Widget* w : widgets) {
		if (w->getBounds().intersects(mouse)) {
			return w->onMouseOver(mouse);
		}
	}
	return nullptr;
}

/*
 * Called when the mouse is hovering over the widget.
 */
void JetMan::Graphics::Panel::onMouseClick(JetMan::Graphics::Rectangle mouse) {
	for (Widget* w : widgets) {
		if (w->getBounds().intersects(mouse)) {
			w->onMouseClick(mouse);
			break;
		}
	}
}

/*
 * Called when the mouse is hovering over the widget.
 */
void JetMan::Graphics::Panel::onMouseOut() {
	for (Widget* w : widgets) {
		w->onMouseOut();
	}
}

// =========================Label====================================
/*
 * Creates a new label with the given text and font.
 */
JetMan::Graphics::Label::Label(std::string l, ALLEGRO_FONT* f) : label(l), font(f), colour(al_map_rgb(0, 0, 0)) {
	JetMan::Graphics::Rectangle bounds = getBounds();
	bounds.setWidth(al_get_text_width(font, l.c_str()));
	bounds.setHeight(al_get_font_line_height(font));
	setBounds(bounds);
}
/*
 * Sets the text of the label.
 */
void JetMan::Graphics::Label::setText(std::string label) {
	this->label = label;
	JetMan::Graphics::Rectangle bounds = getBounds();
	bounds.setWidth(al_get_text_width(font, label.c_str()));
	bounds.setHeight(al_get_font_line_height(font));
	setBounds(bounds);
}

/*
 * Sets the colour of the label's text
 */
void JetMan::Graphics::Label::setColour(ALLEGRO_COLOR colour) {
	this->colour = colour;
}

/*
 * Draws the text.
 */
void JetMan::Graphics::Label::draw() {
	int x, y, width, height;
	al_get_clipping_rectangle(&x, &y, &width, &height);
	JetMan::Graphics::Rectangle bounds = getBounds();
	al_set_clipping_rectangle(bounds.getX() - 10, bounds.getY() - 10, bounds.getX() + bounds.getWidth() + 10, bounds.getY() + bounds.getHeight() + 10);
	al_draw_text(font, colour, bounds.getX(), bounds.getY(), ALLEGRO_ALIGN_LEFT, label.c_str());
	al_set_clipping_rectangle(x, y, width, height);
}

// =========================Button==========================================
/*
 * Creates a new button
 */
JetMan::Graphics::Button::Button(std::string l, ALLEGRO_FONT* f) : Label(l, f), normalBack(al_map_rgb(255, 255, 255)), hoverBack(al_map_rgb(0, 100, 255)) {
	JetMan::Graphics::Rectangle bounds = getBounds();
	bounds.setWidth(al_get_text_width(f, l.c_str()));
	bounds.setHeight(al_get_font_line_height(f));
	setBounds(bounds);
	hover = false;
}

/*
 * Change background colour.
 */
JetMan::Graphics::Widget* JetMan::Graphics::Button::onMouseOver(JetMan::Graphics::Rectangle mouse) {
	hover = true;
	return this;
}

/*
 * Change background colour.
 */
void JetMan::Graphics::Button::onMouseOut() {
	hover = false;
}

/*
 * Draws the text.
 */
void JetMan::Graphics::Button::draw() {
	int x, y, width, height;
	al_get_clipping_rectangle(&x, &y, &width, &height);
	JetMan::Graphics::Rectangle bounds = getBounds();
	al_set_clipping_rectangle(bounds.getX()-10, bounds.getY()-10, bounds.getX()+bounds.getWidth()+10, bounds.getY()+bounds.getHeight()+10);
	ALLEGRO_COLOR back = hover ? hoverBack : normalBack;
	al_draw_filled_rounded_rectangle(bounds.getX() - 10, bounds.getY() - 10, bounds.getX() + bounds.getWidth() + 10, bounds.getY() + bounds.getHeight() + 10, 5, 5, back);
	al_draw_text(font, colour, bounds.getX(), bounds.getY(), ALLEGRO_ALIGN_LEFT, label.c_str());
	al_set_clipping_rectangle(x, y, width, height);
}

// ====================Sprite==================================
/*
 * Sets the velocity of the sprite.
 */
void JetMan::Graphics::Sprite::setVelocity(float dx, float dy) {
	this->dx = dx;
	this->dy = dy;
}

/*
 * Gets the horizontal velocity.
 */
float JetMan::Graphics::Sprite::getVelocityX() {
	return dx;
}

/*
 * Sets the horizontal velocity.
 */
void JetMan::Graphics::Sprite::setVelocityX(float dx) {
	this->dx = dx;
}

/*
 * Gets the vertical velocity.
 */
float JetMan::Graphics::Sprite::getVelocityY() {
	return dy;
}

/*
 * Sets the vertical velocity.
 */
void JetMan::Graphics::Sprite::setVelocityY(float dy) {
	this->dy = dy;
}

/*
 * Updates the position of the sprite based on its velocity and time elapsed.
 */
void JetMan::Graphics::Sprite::update(float delta) {
	JetMan::Graphics::Rectangle bounds = getBounds();
	float x = bounds.getX() + dx*delta;
	float y = bounds.getY() + dy*delta;
	bounds.setX(x);
	bounds.setY(y);
	setBounds(bounds);
}

/*
 * Sets the image of the sprite.
 */
void JetMan::Graphics::Sprite::setImage(ALLEGRO_BITMAP* image) {
	this->image = image;
	JetMan::Graphics::Rectangle bounds = getBounds();
	bounds.setWidth(al_get_bitmap_width(image));
	bounds.setHeight(al_get_bitmap_height(image));
	setBounds(bounds);
}

/*
 * Sets the image of the sprite.
 */
void JetMan::Graphics::Sprite::draw() {
	JetMan::Graphics::Rectangle bounds = getBounds();
	al_draw_bitmap(image, bounds.getX(), bounds.getY(), NULL);
}

/*
 * Creates a new sprite with the given image.
 */
JetMan::Graphics::Sprite::Sprite(ALLEGRO_BITMAP* i) : image(i) {
	JetMan::Graphics::Rectangle bounds = getBounds();
	bounds.setWidth(al_get_bitmap_width(i));
	bounds.setHeight(al_get_bitmap_height(i));
	setBounds(bounds);
}

// =======================InformationBox==========================
/*
 * Creates a new Information Box.
 */
JetMan::Graphics::InformationBox::InformationBox(float width, float height, ALLEGRO_FONT* font) : white(al_map_rgb(255, 255, 255)), black(al_map_rgb(0, 0, 0)) {
	JetMan::Graphics::Rectangle bounds = getBounds();
	bounds.setWidth(width);
	bounds.setHeight(height);
	setBounds(bounds);
	this->font = font;
}

/*
 * Updates the score to be displayed.
 */
void JetMan::Graphics::InformationBox::updateScore(int score) {
	this->score = score;
}

/*
 * Sets the state of the game. A different instruction message will be displayed depending on whether the game
 * is paused or not.
 */
void JetMan::Graphics::InformationBox::setState(State state) {
	this->state = state;
}

/*
 * Draws the InformationBox.
 */
void JetMan::Graphics::InformationBox::draw() {
	std::string scoreT = "Score: ";
	scoreT.append(std::to_string(score));
	const char *scoreText = scoreT.c_str();
	JetMan::Graphics::Rectangle bounds = getBounds();
	al_draw_filled_rectangle(0, 0, bounds.getWidth(), bounds.getHeight(), black);
	al_draw_text(font, white, 20, 35, ALLEGRO_ALIGN_LEFT, scoreText);
	if (state==PAUSED) {
		al_draw_text(font, white, 250, 35, ALLEGRO_ALIGN_LEFT, "Game Paused [Press Esc to quit or Enter to resume]");
	}
	else if(state==ACTIVE){
		al_draw_text(font, white, 250, 35, ALLEGRO_ALIGN_LEFT, "[Press Esc to pause]");
	}
	else if (state == DEMO) {
		al_draw_text(font, white, 250, 10, ALLEGRO_ALIGN_LEFT, "DEMO [Press Esc to quit]");
		al_draw_text(font, white, 250, 40, ALLEGRO_ALIGN_LEFT, "For a small jet boost tap the spacebar key");
		al_draw_text(font, white, 250, 70, ALLEGRO_ALIGN_LEFT, "For a big jet boost hold the spacebar key for a bit longer");
	}
	else {
		al_draw_text(font, white, 250, 35, ALLEGRO_ALIGN_LEFT, "Game Over! [Press Esc to quit or Enter to restart]");
	}
}

// =======================JetManSprite==================================
/*
 * Updates JetMan's velocity by applying gravity.
 */
void JetMan::Graphics::JetManSprite::update(float delta) {
	dy += gravity*delta;
	if (dy > 110) {
		dy = 110;
	}
	JetMan::Graphics::Sprite::update(delta);
}

// ======================Wall======================================
/*
 * Creates a new wall sprite.
 */
JetMan::Graphics::Wall::Wall(ALLEGRO_BITMAP* w, int gapPosition) : Sprite(w) {
	srand(time(NULL));
	this->gapPosition = gapPosition;
	JetMan::Graphics::Rectangle bounds = getBounds();
	for (int i = 0; i < 4; i++) {
		walls[i] = new JetMan::Graphics::Rectangle(0, 0, bounds.getWidth(), bounds.getHeight());
	}
	updateWalls();
}

/*
 * Frees allocated memory.
 */
JetMan::Graphics::Wall::~Wall() {
	for (int i = 0; i < 4; i++) {
		delete walls[i];
	}
}

/*
 * Updates the position of the gap by generating a random number between 1 and 3.
 */
void JetMan::Graphics::Wall::updateGap() {
	gapPosition = (rand() % 4) + 0;
	updateWalls();
}

/*
 * Updates the bounds of the wall rectangles.
 */
void JetMan::Graphics::Wall::updateWalls() {
	JetMan::Graphics::Rectangle mainWall = getBounds();
	JetMan::Graphics::Rectangle* wallBounds;

	int pos = 0;
	for (int i = 0; i < 5; i++) {
		if (gapPosition == i) {
			continue;
		}
		else {
			wallBounds = walls[pos];
			wallBounds->setX(mainWall.getX());
			wallBounds->setY(100 + 100 * i);
			pos++;
		}
	}
}

/*
 * Checks whether the rectangle collides with the wall.
 */
bool JetMan::Graphics::Wall::collides(JetMan::Graphics::Rectangle rect) {
	for (JetMan::Graphics::Rectangle*wall : walls) {
		if (wall->intersects(rect)) {
			return true;
		}
	}
	return false;
}

/*
 * Updates the wall and each wall segments bounds.
 */
void JetMan::Graphics::Wall::update(float delta) {
	JetMan::Graphics::Sprite::update(delta);
	updateWalls();
}

/*
 * Draws the wall with the gap.
 */
void JetMan::Graphics::Wall::draw() {
	for (JetMan::Graphics::Rectangle*wall : walls) {
		al_draw_bitmap(image, wall->getX(), wall->getY(), NULL);
	}
}

/*
 * Need to update the wall bounds when the position is changed.
 */
void JetMan::Graphics::Wall::setPosition(float x, float y) {
	JetMan::Graphics::Sprite::setPosition(x, y);
	updateWalls();
}

/*
 * The position of the gap.
 */
int JetMan::Graphics::Wall::getGapPosition() {
	return gapPosition;
}