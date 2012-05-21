#pragma once

#include <SFGUI/Config.hpp>
#include <SFGUI/SharedPtr.hpp>

#include <SFML/Graphics.hpp>

namespace sfg {

class RendererViewport;

/** Renderer primitive.
 */
class SFGUI_API Primitive {
	public:
		typedef SharedPtr<Primitive> Ptr; //!< Shared pointer.

		/** Primitive vertex
		 */
		struct Vertex {
			sf::Vector2f position;
			sf::Color color;
			sf::Vector2f texture_coordinate;
		};

		/** Ctor.
		 */
		Primitive();

		/** Merge another primitive into this primitive.
		 * @param primitive Primitive to merge into this primitive.
		 */
		void Add( Primitive& primitive );

		/** Add vertex to this primitive.
		 * @param vertex Vertex to add.
		 */
		void AddVertex( const Vertex& vertex );

		/** Set position of this primitive.
		 * @param position Position of this primitive.
		 */
		void SetPosition( const sf::Vector2f& position );

		/** Get position of this primitive.
		 * @return Position of this primitive.
		 */
		const sf::Vector2f& GetPosition() const;

		/** Set viewport this primitive should be drawn in.
		 * @param viewport Viewport this primitive should be drawn in.
		 */
		void SetViewport( const SharedPtr<RendererViewport>& viewport );

		/** Get viewport this primitive is drawn in.
		 * @return Viewport this primitive is drawn in.
		 */
		const SharedPtr<RendererViewport>& GetViewport() const;

		/** Set draw layer of this primitive.
		 * @param layer Draw layer of this primitive.
		 */
		void SetLayer( int layer );

		/** Get draw layer of this primitive.
		 * @return Draw layer of this primitive.
		 */
		int GetLayer() const;

		/** Set draw hierarchy level of this primitive.
		 * Primitives with lower levels are drawn first.
		 * @param level New draw hierarchy level of this primitive.
		 */
		void SetLevel( int level );

		/** Get draw hierarchy level of this primitive.
		 * Primitives with lower levels are drawn first.
		 * @return Draw hierarchy level of this primitive.
		 */
		int GetLevel() const;

		/** Get vertices in this primitive.
		 * @return Vertices in this primitive.
		 */
		std::vector<Vertex>& GetVertices();

		/** Set whether the primitive is synced with the VBO.
		 * @param synced true to flag that primitive is synced with the VBO.
		 */
		void SetSynced( bool synced = true );

		/** Is the primitive synced with the VBO?.
		 * @return true when the primitive is synced with the VBO.
		 */
		bool IsSynced() const;

		/** Flag the primitive for drawing.
		 * @param visible true to draw the primitive.
		 */
		void SetVisible( bool visible );

		/** Is the primitive visible (drawn)?.
		 * @return true when the primitive is visible.
		 */
		bool IsVisible() const;

	private:
		sf::Vector2f m_position;
		SharedPtr<RendererViewport> m_viewport;
		int m_layer;
		int m_level;

		std::vector<Vertex> m_vertices;

		bool m_synced;
		bool m_visible;
};

}
