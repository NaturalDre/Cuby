#ifndef ENGINE_H
#define ENGINE_H

#include <list>

union ALLEGRO_EVENT;
struct ALLEGRO_DISPLAY;
struct ALLEGRO_TIMER;
struct ALLEGRO_EVENT_QUEUE;
class IProcess;
class IGameBoard;
class IGameObject;
class IInputComponent;
class CRenderer;
class CEngine
{
public:
	CEngine(void);
	~CEngine(void);
	/// Initializes engine core.
	/// @note Call before any other functions.
	int Init(void);
	/// Start the game loop.
	int Run(void);

	bool AddGameObject(IGameObject* m_gameObject);
	void RemoveGameObject(IGameObject* m_gameObject);
	bool AddGameObjectAt(size_t index);
	void RemoveGameObjectAt(size_t index);

	/// Add an input component that will be sent 
	/// input data once per frame(if there is any).
	/// @note Function will remove the duplicate if there
	/// is one.
	bool AddInputComponent(IInputComponent* input);
	/// Remove an input component. Removed input components
	/// no longer receive input data.
	void RemoveInputComponent(IInputComponent* input);
	/// Add an input component at a specific location
	/// in the list. Useful for specifying the order things
	/// should receive input data.
	/// @note The function will remove the duplicate if
	/// there is one.
	bool AddInputComponentAt(size_t index);
	/// Remove an input component at a specific location.
	/// @note Does nothing if that index does not exist.
	void RemoveInputComponentAt(size_t index);

	void SetGameBoard(IGameBoard* gameBoard) { m_gameBoard = gameBoard; }
	IGameBoard* GetGameBoard(void) const { return m_gameBoard; }
	CRenderer* GetRenderer(void) { return m_renderer; }

protected:
	/// Update all gameobjects.
	void OnUpdate(void);
	/// Tell all IRenderComponents it's time to draw.
	void OnRender(void);
	// Proxy for OnUpdate();
	void Update(void) { OnUpdate();}
	/// Proxy for OnRender();
	void Render(void) { OnRender(); }
	/// Send events to the IInputComponents
	void PushEvent(const ALLEGRO_EVENT& ev);
private:
	std::list<IGameObject*> m_gameObjects;
	std::list<IInputComponent*> m_inputComponents;
	ALLEGRO_DISPLAY* m_display; /// The game screen
	ALLEGRO_TIMER* m_timer;		/// Timer to manage framerate
	ALLEGRO_EVENT_QUEUE* m_evQ;	/// Holds events generated by the other ALLEGRO.
	CRenderer* m_renderer;		/// Manager to handle rendering.
	IGameBoard* m_gameBoard;	/// The board/game that's being played/rendered.
	bool m_done;				/// Should we close the application?
	bool m_needRedraw;			/// Set to true whenever gameobjects update.
	double m_timeLastUpdated;	/// The time Update() was last called.
};

#endif