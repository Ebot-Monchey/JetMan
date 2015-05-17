// graphics.h contains the class declarations for displayable objects

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include "utils.h"

namespace JetMan {
	namespace Graphics {
		/*
		 * The base class for all objects that can be displayed on the screen.
		 */
		class Displayable {
		public:
			/*
			 * Initialises the bounding rectangle.
			 */
			Displayable();
			/*
			 * Gets the bounding rectangle of the displayable object.
			 */
			JetMan::Utils::Rectangle getBounds();
			/*
			 * Sets the bounding rectangle of the displayable object.
			 */
			void setBounds(JetMan::Utils::Rectangle bounds);
			/*
			 * Draws the displayable object to the screen.
			 */
			virtual void draw() = 0;
		private:
			JetMan::Utils::Rectangle bounds;			// The bounds of the displayable object.
		};

		/*
		 * Represents a user interface component.
		 */
		class Widget : public Displayable {
		public:
			/*
			 * Called when the mouse is hovering over the widget.
			 */
			virtual void onMouseOver(JetMan::Utils::Rectangle mouse) = 0;
			/*
			 * Called when the mouse clicks the widget.
			 */
			virtual void onClick(JetMan::Utils::Rectangle mouse) = 0;
		};

		/*
		 * Widget that can contain other widgets.
		 */
		class Panel : public Widget {
		public:
			/*
			 * Creates a new panel.
			 */
			Panel();
			/*
			 * Adds the widget to this panel.
			 */
			void addWidget(Widget *widget);
			/*
			 * Draws the panel by drawing all its children widgets.
			 */
			void draw();
			/*
			 * Called when the mouse is hovering over the widget.
			 */
			void onMouseOver(JetMan::Utils::Rectangle mouse);
			/*
			 * Called when the mouse clicks the widget.
			 */
			void onClick(JetMan::Utils::Rectangle mouse);
		private:
			std::vector<Widget*> widgets;			// The widgets on the panel.
		};
	}
}

#endif