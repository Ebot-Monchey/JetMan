// Implements the classes found in graphics.h

#include <string>
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

// =========================Label====================================
/*
 * Sets the text of the label.
 */
void JetMan::Graphics::Label::setText(std::string label) {
	this->label = label;
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
	JetMan::Utils::Rectangle rect = getBounds();
	al_draw_text(font, colour, rect.getX(), rect.getY(), ALLEGRO_ALIGN_LEFT, label.c_str());
}