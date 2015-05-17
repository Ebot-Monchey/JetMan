// graphics.h contains the class declarations for displayable objects

#ifndef GRAPHICS_H
#define GRAPHICS_H

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
	}
}

#endif