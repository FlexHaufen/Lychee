#include <Lychee/Lychee.h>
#include "EditorLayer.h"

namespace Lychee {

	class LycheeApp : public Core {
	public:
		LycheeApp()
			: Core() {
            
			LY_INFO("Starting App");
			PushLayer(new EditorLayer());
		}   
	};

	Core* CreateApplication() {
		LY_INFO("Create Application");
		return new LycheeApp();
	}

}
