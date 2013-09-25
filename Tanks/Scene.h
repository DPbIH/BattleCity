#pragma once

#include "GraphicObjectBase.h"
#include "Coordinates.h"
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
	void PinToLevelMap( const Coordinates& levelMapLeftBottom );
	void PinToWindow( const Coordinates& wndLeftBottom );
	Coordinates SceneCoordToWndCoord( const Coordinates& sceneCoord ) const;
	Coordinates LevelMapCoordToSceneCoord( const Coordinates& levelMapCoord ) const;
	Coordinates LevelMapCoordToWndCoord( const Coordinates& sceneCoord ) const;
	bool CheckSceneCoversLevelMapCoord( const Coordinates& coord ) const;
	void Draw();

private:
	void AlignLevelMapPinPoint();
	void DrawBorders();
	void DrawBattlefield();
	void ClearScreen();

	GraphicObjectBase::Ptr followedObj_;

	size_t height_, width_;
	Coordinates wndLeftBottom_, levelMapLeftBottom_;
};