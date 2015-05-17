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
			 * Sets the position to be drawn to.
			 */
			void setPosition(float x, float y);
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
			virtual Widget* onMouseOver(JetMan::Utils::Rectangle mouse) = 0;
			/*
			 * Called when the mouse moves out of this component.
			 */
			virtual void onMouseOut() = 0;
			/*
			 * Called when the mouse clicks the widget.
			 */
			virtual void onMouseClick(JetMan::Utils::Rectangle mouse) = 0;
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
			Widget* onMouseOver(JetMan::Utils::Rectangle mouse);
			/*
			 * Do nothing on mouse click.
			 */
			void onMouseClick(JetMan::Utils::Rectangle mouse);
			/*
			 * Called when the mouse moves out of this component.
			 */
			void onMouseOut();
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
			Label(std::string l, ALLEGRO_FONT* f);
			/*
			 * Changes the text of the label.
			 */
			void setText(std::string label);
			/*
			 * Sets the colour of the label.
			 */
			void setColour(ALLEGRO_COLOR colour);
			/*
			 * Do nothing on mouse over.
			 */
			Widget* onMouseOver(JetMan::Utils::Rectangle mouse) { return nullptr; }
			/*
			 * Do nothing on mouse click.
			 */
			void onMouseClick(JetMan::Utils::Rectangle mouse) {}
			/*
			 * Do nothing on mouse out.
			 */
			void onMouseOut() {}
			/*
			 * Draws the text.
			 */
			void draw();
		protected:
			std::string label;			// The label's text.
			ALLEGRO_FONT* font;			// The font to be used.
			ALLEGRO_COLOR colour;		// The colour for the text.
		};

		/*
		 * Button that can be pressed.
		 */
		class Button : public Label {
		public:
			/*
			 * Creates a new button woth the given text and font
			 */
			Button(std::string l, ALLEGRO_FONT* f);
			/*
			 * Change background colour.
			 */
			Widget* onMouseOver(JetMan::Utils::Rectangle mouse);
			/*
			 * Do nothing on mouse click.
			 */
			void onMouseClick(JetMan::Utils::Rectangle mouse) { onClick(); }
			/*
			 * Change background colour.
			 */
			void onMouseOut();
			/*
			 * To be overridden to perform button click action.
			 */
			virtual void onClick() {}
			/*
			 * Draws the text.
			 */
			void draw();
		private:
			ALLEGRO_COLOR normalBack;		// The colour for the text.
			ALLEGRO_COLOR hoverBack;		// The colour for the text.
			bool hover;						// Whether the mouse is hovering over it or not.
		};

		/*
		 * Represents an object to be moved around the screen.
		 */
		class Sprite : public Displayable {
		public:
			/*
			 * Creates a new sprite with the given image.
			 */
			Sprite(ALLEGRO_BITMAP* image);
			/*
			 * Sets the velocity of the sprite.
			 */
			void setVelocity(float dx, float dy);
			/*
			 * Gets the horizontal velocity.
			 */
			float getVelocityX();
			/*
			 * Sets the horizontal velocity.
			 */
			void setVelocityX(float dx);
			/*
			 * Gets the vertical velocity.
			 */
			float getVelocityY();
			/*
			 * Sets the vertical velocity.
			 */
			void setVelocityY(float dy);
			/*
			 * Updates the position of the sprite based on its velocity and time elapsed.
			 */
			void update(float delta);
			/*
			 * Sets the image of the sprite.
			 */
			void setImage(ALLEGRO_BITMAP* image);
			/*
			 * Draws the sprite to the screen.
			 */
			void draw();
		protected:
			float dx = 0;					// The horizontal velocity
			float dy = 0;					// The vertical velocity
			ALLEGRO_BITMAP* image;			// The sprite's image
		};
	}
}

#endif