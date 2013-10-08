#pragma once

#include "GraphicObjectBase.h"
#include "Coordinates.h"
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

class SceneObjectsVisitor;
class SceneRenderer;
class DrawVisitor;

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
	void InitDrawer();

	GraphicObjectBase::Ptr followedObj_;

	boost::shared_ptr<DrawVisitor> drawer_;
	boost::shared_ptr<SceneRenderer> renderer_;
	boost::shared_ptr<SceneObjectsVisitor> sceneDrawer_;

	size_t height_, width_;
	Coordinates wndLeftBottom_, levelMapLeftBottom_;
};