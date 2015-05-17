// Implements the classes found in graphics.h

#include "graphics.h"
#include "utils.h"

/*
 * Initialises the bounding rectangle.
 */
JetMan::Graphics::Displayable::Displayable() : bounds(JetMan::Utils::Rectangle(0, 0, 0, 0)) {

}

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