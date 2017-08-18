#ifndef BL_CONNECTION_HPP
#define BL_CONNECTION_HPP


//-------------------------------------------------------------------
// FILE:            blConnection.hpp
// CLASS:           blConnection
// BASE CLASS:      blResourceAPI::blIDSystem
//
// PURPOSE:         Based on blResourceAPI::blIDSystem, it forms a base class
//                  used to connect rigid bodies using springs,
//                  dampers, kinematic constraints and more
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    - blResourceAPI::blIDSystem -- To keep count of all
//                                  the connections in a
//                                  program
//
// NOTES:
//
// DATE CREATED:    May/05/2011
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
template<typename blDataType>
class blConnection
{
public: // Constructors and destructors

    // Default constructor

    blConnection(const std::shared_ptr< blRigidBody<blDataType> >& rigidBody1 = std::shared_ptr< blRigidBody<blDataType> >(),
                 const std::shared_ptr< blRigidBody<blDataType> >& rigidBody2 = std::shared_ptr< blRigidBody<blDataType> >(),
                 const blMathAPI::blVector3d<blDataType>& rigidBody1ConnectionPosition = blMathAPI::blVector3d<blDataType>(0,0,0),
                 const blMathAPI::blVector3d<blDataType>& rigidBody2ConnectionPosition = blMathAPI::blVector3d<blDataType>(0,0,0))
    {
        // Copy the bodies
        // pointers

        setRigidBody1(rigidBody1);
        setRigidBody2(rigidBody2);

        // Copy the connection
        // positions

        setRigidBody1ConnectionPosition(rigidBody1ConnectionPosition);
        setRigidBody2ConnectionPosition(rigidBody2ConnectionPosition);
    }

    // Copy constructor

    blConnection(const blConnection<blDataType>& connection)
    {
        // Copy the bodies
        // pointers

        setRigidBody1(connection.getRigidBody1());
        setRigidBody2(connection.getRigidBody2());

        // Copy the connection
        // positions

        setRigidBody1ConnectionPosition(connection.getRigidBody1ConnectionPosition());
        setRigidBody2ConnectionPosition(connection.getRigidBody2ConnectionPosition());
    }

    // Destructor
    ~blConnection()
    {
    }

public: // Public functions

    // Functions used to set/get the
    // rigid bodies connected with
    // this connection

    void                                                    setRigidBody1(const std::shared_ptr< blRigidBody<blDataType> >& rigidBody1);
    void                                                    setRigidBody2(const std::shared_ptr< blRigidBody<blDataType> >& rigidBody2);
    const std::shared_ptr< blRigidBody<blDataType> >&       getRigidBody1()const;
    const std::shared_ptr< blRigidBody<blDataType> >&       getRigidBody2()const;

    // Function used to set the
    // positions where this connection
    // is attached to the rigid bodies

    void                                                    setRigidBody1ConnectionPosition(const blMathAPI::blVector3d<blDataType>& rigidBody1ConnectionPosition);
    void                                                    setRigidBody2ConnectionPosition(const blMathAPI::blVector3d<blDataType>& rigidBody2ConnectionPosition);

    // Function used to get the
    // positions where this connection
    // is attached to the rigid bodies

    const blMathAPI::blVector3d<blDataType>&                getRigidBody1ConnectionPosition()const;
    const blMathAPI::blVector3d<blDataType>&                getRigidBody2ConnectionPosition()const;

    // Function that calculates and
    // applies forces/torques to the
    // rigid bodies

    virtual void                                            calculateAndApplyForcesAndTorques();

    // Function used to know
    // whether this connection
    // has broken or not, maybe
    // due to the rigid bodies
    // moving too far apart, or
    // maybe due to them moving
    // too fast or whatever the
    // reason maybe

    virtual bool                                            hasConnectionBeenBroken()const;

private: // Private variables

    // The rigid bodies connected
    // with this connections

    std::shared_ptr< blRigidBody<blDataType> >              m_rigidBody1;
    std::shared_ptr< blRigidBody<blDataType> >              m_rigidBody2;

    // Positions of where the
    // connection attached to
    // the rigid bodies

    blMathAPI::blVector3d<blDataType>                       m_rigidBody1ConnectionPosition;
    blMathAPI::blVector3d<blDataType>                       m_rigidBody2ConnectionPosition;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blConnection<blDataType>::setRigidBody1(const std::shared_ptr<blRigidBody<blDataType> >& rigidBody1)
{
    m_rigidBody1 = rigidBody1;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blConnection<blDataType>::setRigidBody2(const std::shared_ptr<blRigidBody<blDataType> >& rigidBody2)
{
    m_rigidBody2 = rigidBody2;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const std::shared_ptr<blRigidBody<blDataType> >& blConnection<blDataType>::getRigidBody1()const
{
    return m_rigidBody1;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const std::shared_ptr<blRigidBody<blDataType> >& blConnection<blDataType>::getRigidBody2()const
{
    return m_rigidBody2;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blConnection<blDataType>::setRigidBody1ConnectionPosition(const blMathAPI::blVector3d<blDataType>& rigidBody1ConnectionPosition)
{
    m_rigidBody1ConnectionPosition = rigidBody1ConnectionPosition;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blConnection<blDataType>::setRigidBody2ConnectionPosition(const blMathAPI::blVector3d<blDataType>& rigidBody2ConnectionPosition)
{
    m_rigidBody2ConnectionPosition = rigidBody2ConnectionPosition;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blMathAPI::blVector3d<blDataType>& blConnection<blDataType>::getRigidBody1ConnectionPosition()const
{
    return m_rigidBody1ConnectionPosition;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blMathAPI::blVector3d<blDataType>& blConnection<blDataType>::getRigidBody2ConnectionPosition()const
{
    return m_rigidBody2ConnectionPosition;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blConnection<blDataType>::calculateAndApplyForcesAndTorques()
{
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline bool blConnection<blDataType>::hasConnectionBeenBroken()const
{
    // As a default we make
    // this connection unbreakable

    return false;
}
//-------------------------------------------------------------------


#endif // BL_CONNECTION_HPP
