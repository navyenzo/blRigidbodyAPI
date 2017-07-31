#ifndef BL_RIGIDBODYAPI_HPP
#define BL_RIGIDBODYAPI_HPP


//-------------------------------------------------------------------
// FILE:            blRigidBodyAPI.hpp
// CLASS:           None
// BASE CLASS:      None
//
// PURPOSE:         Simple rigid body physics API
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:
//
// NOTES:
//
// DATE CREATED:    Nov/08/2010
// DATE UPDATED:
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Enums needed for this file
//-------------------------------------------------------------------
//-------------------------------------------------------------------


//-------------------------------------------------------------------
namespace blRigidBodyAPI
{
    // A base class to add mass and
    // rotational inertia to an object

    #include "blInertia.hpp"



    // A base class to add position to
    // an object together with the ability
    // to translate the object

    #include "blPosition.hpp"



    // A base class to add
    // velocity to an object

    #include "blVelocity.hpp"



    // A base class to add
    // an angular velocity
    // to an object

    #include "blAngularVelocity.hpp"



    // A base class to add motion limits and
    // restitution coefficients

    #include "blRestitution.hpp"



    // Based on blRestitution, it adds orientation
    // to an object with the ability to rotate the
    // object, and determine its three x,y,z
    // rotation axes and its rotation angle/axis
    // and its rotation axis

    #include "blOrientation.hpp"



    // A base class to add a size to an object
    // with the ability to scale the object

    #include "blSize.hpp"



    // A base class to add damping
    // energy losses to an object

    #include "blDamping.hpp"



    // Based on classes blIDSystem,blPosition,blVelocity,
    // blOrientation,blAngularVelocity and blInertia,
    // blDamping, blRestitution, it combines all these
    // properties into an object to represent a rigid
    // body and its dynamics

    #include "blRigidBody.hpp"



    // Based on blIDSystem, it forms a base class
    // used to connect rigid bodies using springs,
    // dampers, kinematic constraints and more

    #include "blConnection.hpp"



    // Based on blConnection, this class adds an
    // array of coefficients used to calculate
    // a polynomial spring force between two bodies
    // where the array of coefficients represents the
    // polynomial coefficients

    #include "blPolySpring.hpp"



    // Based on blRigidBody, it adds a set of rigid
    // bodies used to simulate a system of rigid
    // bodies

    #include "blRigidBodySystem.hpp"
}
//-------------------------------------------------------------------


#endif // BL_RIGIDBODYAPI_HPP
