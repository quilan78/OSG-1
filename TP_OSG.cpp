// base
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osg/Material>
#include <osg/StateSet>
#include <osg/MatrixTransform>
#include <osg/Geometry>
#include <osgDB/ReadFile>
// Keyboard input
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>

#include <iostream>


int main()
{
/* OBJECTS CREATION */

	//Creating the viewer	
	osgViewer::Viewer viewer ;

	//Creating the root node
	osg::ref_ptr<osg::Group> root (new osg::Group);

	// StateSet de root
	osg::ref_ptr<osg::StateSet> rootStateSet ( root->getOrCreateStateSet() );
	
	//The geode containing our shape
   	osg::ref_ptr<osg::Geode> myshapegeode1 (new osg::Geode);
   	osg::ref_ptr<osg::Geode> myshapegeode2 (new osg::Geode);
   	osg::ref_ptr<osg::Geode> myshapegeode3 (new osg::Geode);
   	osg::ref_ptr<osg::Geode> myshapegeode4 (new osg::Geode);

	//Defining the statesets
	osg::ref_ptr<osg::StateSet> nodeStateSet1 ( myshapegeode1->getOrCreateStateSet() );
	osg::ref_ptr<osg::StateSet> nodeStateSet2 ( myshapegeode2->getOrCreateStateSet() );
	osg::ref_ptr<osg::StateSet> nodeStateSet3 ( myshapegeode3->getOrCreateStateSet() );
	osg::ref_ptr<osg::StateSet> nodeStateSet4 ( myshapegeode4->getOrCreateStateSet() );
	
	//Our shape: a capsule, it could have been any other geometry (a box, plane, cylinder etc.)
	osg::ref_ptr<osg::Capsule> myCapsule (new osg::Capsule(osg::Vec3f(),1,2));
	osg::ref_ptr<osg::Sphere> mySphere (new osg::Sphere(osg::Vec3f(),2));
	osg::ref_ptr<osg::Cylinder> myCylinder (new osg::Cylinder(osg::Vec3f(),1,4));
	osg::ref_ptr<osg::Cone> myCone ( new osg::Cone(osg::Vec3f(),3,4));
	
	// Creation of PATs
	osg::ref_ptr<osg::PositionAttitudeTransform> myTransform1 ( new osg::PositionAttitudeTransform);
	osg::ref_ptr<osg::PositionAttitudeTransform> myTransform2 ( new osg::PositionAttitudeTransform);
	osg::ref_ptr<osg::PositionAttitudeTransform> myTransform3 ( new osg::PositionAttitudeTransform);
	osg::ref_ptr<osg::PositionAttitudeTransform> myTransform4 ( new osg::PositionAttitudeTransform);
	osg::ref_ptr<osg::PositionAttitudeTransform> myTransform5 ( new osg::PositionAttitudeTransform);

	// Parametring PATs
	myTransform1->setPosition(osg::Vec3f(3,0,3));
	myTransform2->setPosition(osg::Vec3f(-3,0,-3));
	myTransform3->setPosition(osg::Vec3f(-3,0,3));
	myTransform4->setPosition(osg::Vec3f(3,0,-3));
	myTransform5->setPosition(osg::Vec3f(0,0,-3));

	//Our shape drawable
	osg::ref_ptr<osg::ShapeDrawable> capsuledrawable (new osg::ShapeDrawable(myCapsule.get()));
	osg::ref_ptr<osg::ShapeDrawable> cylinderdrawable (new osg::ShapeDrawable(myCylinder.get()));
	osg::ref_ptr<osg::ShapeDrawable> spheredrawable (new osg::ShapeDrawable(mySphere.get()));
	osg::ref_ptr<osg::ShapeDrawable> conedrawable (new osg::ShapeDrawable(myCone.get()));

	/*
	Partie enlevée car nous utilisons maintenant des stateset
	
	// Setting the colors
	capsuledrawable->setColor(osg::Vec4(255,0,0,0));
	cylinderdrawable->setColor(osg::Vec4(0,255,0,0));
	spheredrawable->setColor(osg::Vec4(0,255,255,0));
	conedrawable->setColor(osg::Vec4(0,0,255,0));
	*/

/* TERRAIN */
	// Create transformation node
	osg::ref_ptr<osg::MatrixTransform> terrainScaleMAT (new osg::MatrixTransform);

	// Scale matrix
	osg::Matrix terrainScaleMatrix;
	terrainScaleMatrix.makeScale(osg::Vec3f(0.1,0.1,0.1));

	//Loading the terrain node
	osg::ref_ptr<osg::Node> terrainnode (osgDB::readNodeFile("Terrain2.3ds"));

	//Set transformation node parameters
	terrainScaleMAT->addChild(terrainnode);
	terrainScaleMAT->setMatrix(terrainScaleMatrix);

/* TEXTURES */
	
	//Getting the state set of the geode
	//osg::ref_ptr<osg::StateSet> textureNodeStateSet (terrainnode->getOrCreateStateSet() );

	//Loading texture image object
	osg::ref_ptr<osg::Image> image (osgDB::readImageFile("wood.png"));

	//Bind the image to a 2D texture object
	osg::ref_ptr<osg::Texture2D> tex (new osg::Texture2D);
	tex->setImage(image);
	//Applying texture on the object
	nodeStateSet1->setTextureAttributeAndModes(0,tex);

/* LIGHTING */
	//Create nodes

	osg::ref_ptr<osg::Group> lightGroup1 (new osg::Group);
	osg::ref_ptr<osg::Group> lightGroup2 (new osg::Group);
	osg::ref_ptr<osg::LightSource> lightSource1 = new osg::LightSource;
	osg::ref_ptr<osg::LightSource> lightSource2 = new osg::LightSource;

	//Create a local light
	osg::Vec4f lightPosition1(-5,-5,0,0);
	osg::Vec4f lightPosition2(5,5,0,0);

	osg::ref_ptr<osg::Light> myLight1 = new osg::Light;
	myLight1->setLightNum(0);
	myLight1->setPosition(lightPosition1);
	myLight1->setDiffuse(osg::Vec4f(1,0,0,0));
	myLight1->setSpecular(osg::Vec4f(1,0,0,0));
	myLight1->setConstantAttenuation(0.1);
	
	osg::ref_ptr<osg::Light> myLight2 = new osg::Light;
	myLight2->setLightNum(1);
	myLight2->setPosition(lightPosition2);
	myLight2->setDiffuse(osg::Vec4f(0,0,1,0));
	myLight2->setSpecular(osg::Vec4f(0,0,1,0));
	myLight2->setConstantAttenuation(0.1);

	//Set light source parameters
	lightSource1->setLight(myLight1.get());

	//Set light source parameters
	lightSource2->setLight(myLight2.get());

	//Add to light source group
	lightGroup1->addChild(lightSource1.get());
	lightGroup2->addChild(lightSource2.get());

	//Light markers: small spheres
   	osg::ref_ptr<osg::Geode> marker1 (new osg::Geode);
	osg::ref_ptr<osg::Sphere> sphereMarker1 (new osg::Sphere(osg::Vec3f(-5,-5,0),0.5));
	osg::ref_ptr<osg::ShapeDrawable> sphereDrawableMarker1 (new osg::ShapeDrawable(sphereMarker1.get()));
	marker1->addDrawable(sphereDrawableMarker1.get());
	root->addChild(marker1.get());

   	osg::ref_ptr<osg::Geode> marker2 (new osg::Geode);
	osg::ref_ptr<osg::Sphere> sphereMarker2 (new osg::Sphere(osg::Vec3f(5,5,0),0.5));
	osg::ref_ptr<osg::ShapeDrawable> sphereDrawableMarker2 (new osg::ShapeDrawable(sphereMarker2.get()));
	marker2->addDrawable(sphereDrawableMarker2.get());
	root->addChild(marker2.get());
	
	// Allumage des lumières
	rootStateSet->setMode(GL_LIGHT0, osg::StateAttribute::ON);
	rootStateSet->setMode(GL_LIGHT1, osg::StateAttribute::ON);
/* SCENE GRAPH*/

	// Add the shape drawable to the geode

	// Question 3.1
	myshapegeode1->addDrawable(capsuledrawable.get());
	myshapegeode2->addDrawable(cylinderdrawable.get());
	myshapegeode3->addDrawable(spheredrawable.get());
	myshapegeode4->addDrawable(conedrawable.get());

	/*
	// Question 3.3
	myshapegeode1->addDrawable(cylinderdrawable.get());
	myshapegeode2->addDrawable(cylinderdrawable.get());
	myshapegeode3->addDrawable(cylinderdrawable.get());
	myshapegeode4->addDrawable(cylinderdrawable.get());*/

	// Add the transform to the scene graph root (Group)
	root->addChild(myTransform1.get());
	root->addChild(myTransform2.get());
	root->addChild(myTransform3.get());
	root->addChild(myTransform4.get());
	root->addChild(lightGroup1.get());
	root->addChild(lightGroup2.get());
	root->addChild(myTransform5.get());

	// Add the geode to the transforms
	myTransform1->addChild(myshapegeode1);
	myTransform2->addChild(myshapegeode2);
	myTransform3->addChild(myshapegeode3);
	myTransform4->addChild(myshapegeode4);
	myTransform5->addChild(terrainScaleMAT.get());


	// Set the scene data
	viewer.setSceneData( root.get() ); 

/* KEYBOARD INPUT */
	
 	//Stats Event Handler s key
	viewer.addEventHandler(new osgViewer::StatsHandler);

	//Windows size handler
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
	
	// add the state manipulator
    	viewer.addEventHandler( new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()) );

/* MATERIAL */

	//Creation des materials
	osg::ref_ptr<osg::Material> material1 (new osg::Material);
	osg::ref_ptr<osg::Material> material2 (new osg::Material);
	osg::ref_ptr<osg::Material> material3 (new osg::Material);
	osg::ref_ptr<osg::Material> material4 (new osg::Material);

	//Setting material 1 - capsule
	material1->setAmbient(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(7.5f,5.3f,1.9f,1));
	material1->setDiffuse(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(0,0,0,1));
	material1->setSpecular(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(0,0,0,1));
	material1->setEmission(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(0,0,0,0));
	material1->setShininess(osg::Material::Face::FRONT_AND_BACK, 0);

	//Setting material 2 - cylindre
	material2->setAmbient(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(0,7,0,0)); // entre 0 et 10
	material2->setDiffuse(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(0,0,0.8,0)); // entre 0 et 1
	material2->setSpecular(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(1,0,0,0)); // entre 0 et 1
	material2->setEmission(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(0,0,0,0)); // entre 0 et 1
	material2->setShininess(osg::Material::Face::FRONT_AND_BACK,50); // entre 0 et 128

	//Setting material 3 - sphere
	material3->setAmbient(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(0,0,7,0));
	material3->setDiffuse(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(0.4,0.4,0.4,0));
	material3->setSpecular(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(0,0,1,0));
	material3->setEmission(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(0,0,0,0));
	material3->setShininess(osg::Material::Face::FRONT_AND_BACK, 128);

	//Setting material 4 - cone
	material4->setAmbient(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(0,0,0.3,0));
	material4->setDiffuse(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(1,0,0,0));
	material4->setSpecular(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(0,0,0.2,0));
	material4->setEmission(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(0,0,0,0));
	material4->setShininess(osg::Material::Face::FRONT_AND_BACK, 0);


	//Attaching the materials
	nodeStateSet1->setAttribute(material1);
	nodeStateSet2->setAttribute(material2);
	nodeStateSet3->setAttribute(material3);
	nodeStateSet4->setAttribute(material4);

/* START VIEWER */

	//The viewer.run() method starts the threads and the traversals.
	return (viewer.run());
}
