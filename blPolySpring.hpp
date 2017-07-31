#ifndef BL_POLYSPRING_HPP
#define BL_POLYSPRING_HPP


//-------------------------------------------------------------------
// FILE:            blPolySpring.hpp
// CLASS:           blPolySpring
// BASE CLASS:      blConnection
//
// PURPOSE:         Based on blConnection, this class adds an
//                  array of coefficients used to calculate
//                  a polynomial spring force between two bodies
//                  where the array of coefficients represents the
//                  polynomial coefficients
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    - blConnection and all its dependencies
//
// NOTES:           - This class uses an array of coefficients
//                    to calculate a polynomial spring force
//                    between two bodies.
//                    - For example:
//                      - When an array equals [0][3.5][0][2.5],
//                        then the total spring force equals:
//                        - force = 0 + 3.5*x + 0*x*x + 2.5*x*x*x,
//                          where "x" represents the elongated
//                          distance of the spring from its
//                          natural length
//
// DATE CREATED:    May/17/2011
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
class blPolySpring : public blConnection<blDataType>
{
public: // Constructors and destructors

    // Default constructor

    blPolySpring(const blDataType& naturalLength = 1,
                 const std::shared_ptr< blRigidBody<blDataType> >& rigidBody1 = std::shared_ptr< blRigidBody<blDataType> >(),
                 const std::shared_ptr< blRigidBody<blDataType> >& rigidBody2 = std::shared_ptr< blRigidBody<blDataType> >(),
                 const blMathAPI::blVector3d<blDataType>& rigidBody1ConnectionPosition = blMathAPI::blVector3d<blDataType>(0,0,0),
                 const blMathAPI::blVector3d<blDataType>& rigidBody2ConnectionPosition = blMathAPI::blVector3d<blDataType>(0,0,0))
                 : blConnection<blDataType>(rigidBody1,
                                            rigidBody2,
                                            rigidBody1ConnectionPosition,
                                            rigidBody2ConnectionPosition)
    {
        // set the natural length

        setNaturalLength(naturalLength);

        // Initialize the coefficients
        // to represent a linear spring

        blDataType coeffs[] = {0,1};
        setCoeffs(coeffs);
    }

    // Copy constructor

    blPolySpring(const blPolySpring<blDataType>& spring1)
                 : blConnection<blDataType>(spring1)
    {
        // Copy the spring's
        // natural length

        setNaturalLength(spring1.getNaturalLength());

        // Copy the coefficients

        setCoeffs(spring1.getCoeffs());
    }

    // Destructor

    ~blPolySpring()
    {
    }

public: // Public functions

    // Functions used to set/get
    // the spring's natural length

    void                                            setNaturalLength(const blDataType& naturalLength);
    const blDataType&                               getNaturalLength()const;

    // Functions used to set the
    // array of coefficients

    template<int numOfCoeffs>
    void                                            setCoeffs(const blDataType(&coeffs)[numOfCoeffs]);
    void                                            setCoeffs(const std::vector<blDataType>& coeffs);

    // Function used to get the
    // array of coefficients

    const std::vector<blDataType>&                  getCoeffs()const;

    // Function that calculates and
    // applies forces/torques to the
    // rigid bodies

    virtual void                                    calculateAndApplyForcesAndTorques();

    // Function used to know
    // whether this connection
    // has broken or not, maybe
    // due to the rigid bodies
    // moving too far apart, or
    // maybe due to them moving
    // too fast or whatever the
    // reason maybe

    virtual bool                                    hasConnectionBeenBroken()const;

protected: // Protected variables

    // The spring's natural length

    blDataType                                      m_naturalLength;

    // The array of coefficients

    std::vector<blDataType>                         m_coeffs;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blPolySpring<blDataType>::setNaturalLength(const blDataType& naturalLength)
{
    m_naturalLength = naturalLength;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType& blPolySpring<blDataType>::getNaturalLength()const
{
    return m_naturalLength;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<int numOfCoeffs>
inline void blPolySpring<blDataType>::setCoeffs(const blDataType(&coeffs)[numOfCoeffs])
{
    m_coeffs = std::vector<blDataType>(coeffs,coeffs + sizeof(coeffs)/sizeof(coeffs[0]));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blPolySpring<blDataType>::setCoeffs(const std::vector<blDataType>& coeffs)
{
    m_coeffs = coeffs;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const std::vector<blDataType>& blPolySpring<blDataType>::getCoeffs()const
{
    return m_coeffs;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blPolySpring<blDataType>::calculateAndApplyForcesAndTorques()
{
    // Step 1:  Check that we have valid
    //          rigid bodies

    if(this->m_rigidBody1.use_count() <= 0 ||
       this->m_rigidBody2.use_count() <= 0)
    {
        // Error -- Not all rigid bodies
        //          are attached to this
        //          spring

        return;
    }

    // Step 2:  Transform the coonection
    //          positions from body
    //          coordinates to system
    //          coordinates

    blMathAPI::blVector3d<blDataType> Pos1 = this->m_rigidBody1ConnectionPosition;
    blMathAPI::blVector3d<blDataType> Pos2 = this->m_rigidBody2ConnectionPosition;

    this->m_rigidBody1->fromBodyToSystemCoordinates(Pos1);
    this->m_rigidBody2->fromBodyToSystemCoordinates(Pos2);

    // Step 2:  calculate the spring's
    //          distance vector

    blMathAPI::blVector3d<blDataType> distanceVector = Pos2 - Pos1;

    // Step 3:  calculate the spring's
    //          elongation

    blDataType elongation = distanceVector.getMagnitude() - m_naturalLength;

    // Step 3:  Normalize the
    //          distance vector

    distanceVector.normalize();

    // Step 4:  calculate the
    //          force magnitude

    blDataType force = 0;
    for(int i = 0; i < m_coeffs.size(); ++i)
    {
        force += m_coeffs[i] * std::pow(elongation,i);
    }

    // Step 5:  Finally we apply the calculated
    //          force both as a force and torque
    //          to the rigid bodies

    this->m_rigidBody1->addForceAndTorque(force*distanceVector,this->m_rigidBody1ConnectionPosition);
    this->m_rigidBody2->addForceAndTorque(-force*distanceVector,this->m_rigidBody2ConnectionPosition);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline bool blPolySpring<blDataType>::hasConnectionBeenBroken()const
{
    // As a default we make
    // this connection unbreakable

    return false;
}
//-------------------------------------------------------------------


#endif // BL_POLYSPRING_HPP
