#ifndef PROCESS_H
#define PROCESS_H

class IProcess
{
public:
	bool IsEnabled(void) const { return m_enabled; }
	void SetEnabled(bool isEnabled) { m_enabled = isEnabled; }
	
	int GetPriority(void) const { return m_priority; }
	void Start(void) { OnStart(); }
	void Update(double dt) { OnUpdate(dt); }
	void End(void) { OnEnd(); }

protected:
	IProcess(bool enabled = true, int priority = 0): m_enabled(enabled), m_priority(priority) { }
	virtual void OnStart(void) = 0;	
	virtual void OnUpdate(double dt) = 0;
	virtual void OnEnd(void) = 0;

private:
	bool m_enabled;
	int m_priority;
}

#endif