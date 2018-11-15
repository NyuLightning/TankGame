#ifndef INPUTREGISTRY_H
#define INPUTREGISTRY_H

#include "flystickinput.h"
#include "keyboardinput.h"
#include "mouseinput.h"
#include "trackinginput.h"


class InputRegistry
{
public:
    /*!
     * \brief getInstance
     * Singleton-Abruf, Thread sicher
     * \return Die Instanz der InputRegistry
     */
    static InputRegistry& getInstance();

    /*!
     * \brief getFlystickInput
     * Erstellt eine FlystickInput-Instanz, falls nicht vorhanden, und gibt diese zurück
     * \return Eine FlystickInput-Instanz
     */
    FlystickInput* getFlystickInput();

    /*!
     * \brief getKeyboardInput
     * Erstellt eine KeyboardInput-Instanz, falls nicht vorhanden, und gibt diese zurück
     * \return Eine KeyboardInput-Instanz
     */
    KeyboardInput* getKeyboardInput();

    /*!
     * \brief getMouseInput
     * Erstellt eine MouseInput-Instanz, falls nicht vorhanden, und gibt diese zurück
     * \return Eine MouseInput-Instanz
     */
    MouseInput* getMouseInput();

    /*!
     * \brief getVrpnInput
     * Erstellt eine VRPNInput-Instanz, falls nicht vorhanden, und gibt diese zurück
     * \return Eine VRPNInput-Instanz
     */
    TrackingInput* getTrackingInput();

    bool hasFlystickInput();              /*!< Prüft, ob eine FlystickInput-Instanz vorhanden ist */
    bool hasKeyboardInput();              /*!< Prüft, ob eine KeyboardInput-Instanz vorhanden ist */
    bool hasMouseInput();                 /*!< Prüft, ob eine MouseInput-Instanz vorhanden ist */
    bool hasTrackingInput();              /*!< Prüft, ob eine VRPNInput-Instanz vorhanden ist */
private:
    explicit InputRegistry();
    virtual ~InputRegistry();

    FlystickInput* m_flyIn;
    KeyboardInput* m_keyIn;
    MouseInput* m_mouseIn;
    TrackingInput* m_trackIn;
};

#endif // INPUTREGISTRY_H
