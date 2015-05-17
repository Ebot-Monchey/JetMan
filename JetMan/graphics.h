// graphics.h contains the class declarations for displayable objects

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <string>
#include <allegro5/allegro_font.h>
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
			Displayable() : bounds(JetMan::Utils::Rectangle(0, 0, 0, 0)) {}
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
			 * Draws the displayable object to the screen.
			 */
			virtual void draw() = 0;
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
			Panel() {}
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

		/*
		 * A label of text.
		 */
		class Label : public Widget {
		public:
			/*
			 * Creates a new label with the given text and font.
			 */
			Label(std::string l, ALLEGRO_FONT* f) : label(l), font(f), colour(al_map_rgb(0, 0, 0)) {}
			/*
			 * Changes the text of the label.
			 */
			void setText(std::string label);
			/*
			 * Sets the colour of the label.
			 */
			void setColour(ALLEGRO_COLOR colour);
			/*
			 * Sets the position to be drawn to.
			 */
			void setPosition(float x, float y);
			/*
			 * Do nothing on mouse over.
			 */
			void onMouseOver(JetMan::Utils::Rectangle mouse) {}
			/*
			 * Do nothing on mouse click.
			 */
			void onClick(JetMan::Utils::Rectangle mouse) {}
			/*
			 * Draws the text.
			 */
			void draw();
		private:
			std::string label;			// The label's text.
			ALLEGRO_FONT* font;			// The font to be used.
			ALLEGRO_COLOR colour;		// The colour for the text.
		};
	}
}

#endif