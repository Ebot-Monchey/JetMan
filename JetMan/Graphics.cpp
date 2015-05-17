// Implements the classes found in graphics.h

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
	JetMan::Utils::Rectangle widgetBounds = (*widget).getBounds();
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
		(*w).draw();
	}
	al_set_clipping_rectangle(x, y, width, height);
}

/*
 * Called when the mouse is hovering over the widget.
 */
void JetMan::Graphics::Panel::onMouseOver(JetMan::Utils::Rectangle mouse) {
	for (Widget* w : widgets) {
		if ((*w).getBounds().intersects(mouse)) {
			(*w).onMouseOver(mouse);
			break;
		}
	}
}

/*
 * Called when the mouse is hovering over the widget.
 */
void JetMan::Graphics::Panel::onClick(JetMan::Utils::Rectangle mouse) {
	for (Widget* w : widgets) {
		if ((*w).getBounds().intersects(mouse)) {
			(*w).onClick(mouse);
			break;
		}
	}
}