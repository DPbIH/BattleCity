#pragma once

#include "Locatable2D.h"
#include "GraphicObjectBase.h"
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>



class Scene
	: boost::noncopyable
{
public:
	typedef boost::shared_ptr<Scene> Ptr;

	Scene();
	void SetFollowedObject( const GraphicObjectBase::Ptr& obj );
	void SetSize( size_t height, size_t width );
	void PinToLevelMapCoordinaets( size_t levelMapLeftBottomX, size_t levelMapLeftBottomY );
	void PinToWindowCordinates( size_t wndLeftBottomX, size_t wndLeftBottomY );
	void SceneCoordinatesToWndCoordinates( size_t sceneX, size_t sceneY, size_t& consoleWndX, size_t& consoleWndY ) const;
	void LevelMapCoordinatesToSceneCoordinates( size_t levelMapX, size_t levelMapY, size_t& sceneX, size_t& sceneY ) const;
	void LevelMapCoordinatesToWndCoordinates( size_t levelMapX, size_t levelMapY, size_t& consoleWndX, size_t& consoleWndY ) const;
	bool CheckLevelMapCoordinatesAreCovered( size_t levelMapX, size_t levelMapY ) const;
	void Draw();

private:
	void AlignCoveredLevelMapArea();
	void DrawBorders();
	void DrawBattlefield();

	GraphicObjectBase::Ptr followedObj_;

	size_t height_, width_,
		wndLeftBottomX_, wndLeftBottomY_,
		levelMapLeftBottomX_, levelMapLeftBottomY_;
};