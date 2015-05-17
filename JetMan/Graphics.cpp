// Implements the classes found in graphics.h

#include <string>
#include <allegro5/allegro_primitives.h>
#include "graphics.h"
#include "utils.h"

// ===================================Displayable=======================================
/*
 * Gets the bounding rectangle of the displayable object.
 */
JetMan::Utils::Rectangle JetMan::Graphics::Displayable::getBounds() {
	return bounds;
}

/*
 * Sets the bounding rectangle of the displayable object.
 */
void JetMan::Graphics::Displayable::setBounds(JetMan::Utils::Rectangle bounds) {
	this->bounds = bounds;
}

// ===============================Panel================================================
/*
 * Adds the widget to the panel.
 */
void JetMan::Graphics::Panel::addWidget(JetMan::Graphics::Panel::Widget* widget) {
	JetMan::Utils::Rectangle panelBounds = getBounds();
	JetMan::Utils::Rectangle widgetBounds = widget->getBounds();
	widgetBounds.setBounds(widgetBounds.getX() + panelBounds.getX(), widgetBounds.getY() + panelBounds.getY(), widgetBounds.getWidth(), widgetBounds.getHeight());
	widgets.push_back(widget);
}

/*
 * Draws the panel by drawing all its children widgets.
 */
void JetMan::Graphics::Panel::draw() {
	int x, y, width, height;
	al_get_clipping_rectangle(&x, &y, &width, &height);
	JetMan::Utils::Rectangle bounds = getBounds();
	al_set_clipping_rectangle(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight());
	for (Widget* w : widgets) {
		w->draw();
	}
	al_set_clipping_rectangle(x, y, width, height);
}

/*
 * Called when the mouse is hovering over the widget.
 */
void JetMan::Graphics::Panel::onMouseOver(JetMan::Utils::Rectangle mouse) {
	for (Widget* w : widgets) {
		if (w->getBounds().intersects(mouse)) {
			w->onMouseOver(mouse);
			break;
		}
	}
}

/*
 * Called when the mouse is hovering over the widget.
 */
void JetMan::Graphics::Panel::onClick(JetMan::Utils::Rectangle mouse) {
	for (Widget* w : widgets) {
		if (w->getBounds().intersects(mouse)) {
			w->onClick(mouse);
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
	JetMan::Utils::Rectangle bounds = getBounds();
	bounds.setWidth(al_get_text_width(font, l.c_str()));
	bounds.setHeight(al_get_font_line_height(font));
	setBounds(bounds);
}
/*
 * Sets the text of the label.
 */
void JetMan::Graphics::Label::setText(std::string label) {
	this->label = label;
	JetMan::Utils::Rectangle bounds = getBounds();
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

void JetMan::Graphics::Label::setPosition(float x, float y) {
	JetMan::Utils::Rectangle rect = getBounds();
	rect.setX(x);
	rect.setY(y);
	setBounds(rect);
}

/*
 * Draws the text.
 */
void JetMan::Graphics::Label::draw() {
	int x, y, width, height;
	al_get_clipping_rectangle(&x, &y, &width, &height);
	JetMan::Utils::Rectangle bounds = getBounds();
	al_set_clipping_rectangle(bounds.getX() - 10, bounds.getY() - 10, bounds.getX() + bounds.getWidth() + 10, bounds.getY() + bounds.getHeight() + 10);
	al_draw_text(font, colour, bounds.getX(), bounds.getY(), ALLEGRO_ALIGN_LEFT, label.c_str());
	al_set_clipping_rectangle(x, y, width, height);
}

// =========================Button==========================================
/*
 * Creates a new button
 */
JetMan::Graphics::Button::Button(std::string l, ALLEGRO_FONT* f) : Label(l, f), normalBack(al_map_rgb(255, 255, 255)), hoverBack(al_map_rgb(0, 100, 255)) {
	JetMan::Utils::Rectangle bounds = getBounds();
	bounds.setWidth(al_get_text_width(f, l.c_str()));
	bounds.setHeight(al_get_font_line_height(f));
	setBounds(bounds);
	hover = false;
}

/*
 * Change background colour.
 */
void JetMan::Graphics::Button::onMouseOver(JetMan::Utils::Rectangle mouse) {
	hover = true;
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
	JetMan::Utils::Rectangle bounds = getBounds();
	al_set_clipping_rectangle(bounds.getX()-10, bounds.getY()-10, bounds.getX()+bounds.getWidth()+10, bounds.getY()+bounds.getHeight()+10);
	ALLEGRO_COLOR back = hover ? hoverBack : normalBack;
	al_draw_filled_rounded_rectangle(bounds.getX() - 10, bounds.getY() - 10, bounds.getX() + bounds.getWidth() + 10, bounds.getY() + bounds.getHeight() + 10, 5, 5, back);
	al_draw_text(font, colour, bounds.getX(), bounds.getY(), ALLEGRO_ALIGN_LEFT, label.c_str());
	al_set_clipping_rectangle(x, y, width, height);
}