#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>

static const unsigned char qt_resource_tree[] = {
0,
0,0,0,0,2,0,0,0,7,0,0,0,1,0,0,0,
118,0,0,0,0,0,1,0,0,0,0,0,0,0,142,0,
2,0,0,0,3,0,0,0,41,0,0,1,66,0,0,0,
0,0,1,0,0,0,0,0,0,0,80,0,0,0,0,0,
1,0,0,0,0,0,0,1,100,0,2,0,0,0,18,0,
0,0,8,0,0,0,58,0,0,0,0,0,1,0,0,0,
0,0,0,0,8,0,0,0,0,0,1,0,0,0,0,0,
0,2,144,0,0,0,0,0,1,0,0,0,0,0,0,2,
80,0,0,0,0,0,1,0,0,0,0,0,0,2,246,0,
0,0,0,0,1,0,0,0,0,0,0,6,6,0,0,0,
0,0,1,0,0,0,0,0,0,2,180,0,0,0,0,0,
1,0,0,0,0,0,0,3,66,0,2,0,0,0,3,0,
0,0,38,0,0,4,190,0,2,0,0,0,5,0,0,0,
33,0,0,5,216,0,0,0,0,0,1,0,0,0,0,0,
0,2,116,0,0,0,0,0,1,0,0,0,0,0,0,2,
44,0,0,0,0,0,1,0,0,0,0,0,0,2,212,0,
0,0,0,0,1,0,0,0,0,0,0,2,10,0,0,0,
0,0,1,0,0,0,0,0,0,3,184,0,2,0,0,0,
7,0,0,0,26,0,0,3,34,0,0,0,0,0,1,0,
0,0,0,0,0,1,212,0,0,0,0,0,1,0,0,0,
0,0,0,1,160,0,0,0,0,0,1,0,0,0,0,0,
0,1,122,0,0,0,0,0,1,0,0,0,0,0,0,5,
156,0,0,0,0,0,1,0,0,0,0,0,0,4,122,0,
0,0,0,0,1,0,0,0,0,0,0,4,20,0,0,0,
0,0,1,0,0,0,0,0,0,4,54,0,0,0,0,0,
1,0,0,0,0,0,0,4,154,0,0,0,0,0,1,0,
0,0,0,0,0,4,86,0,0,0,0,0,1,0,0,0,
0,0,0,3,206,0,0,0,0,0,1,0,0,0,0,0,
0,3,240,0,0,0,0,0,1,0,0,0,0,0,0,4,
216,0,0,0,0,0,1,0,0,0,0,0,0,5,80,0,
0,0,0,0,1,0,0,0,0,0,0,5,40,0,0,0,
0,0,1,0,0,0,0,0,0,5,2,0,0,0,0,0,
1,0,0,0,0,0,0,5,120,0,0,0,0,0,1,0,
0,0,0,0,0,3,152,0,0,0,0,0,1,0,0,0,
0,0,0,3,84,0,0,0,0,0,1,0,0,0,0,0,
0,3,112,0,0,0,0,0,1,0,0,0,0,0,0,1,
14,0,0,0,0,0,1,0,0,0,0,0,0,0,220,0,
0,0,0,0,1,0,0,0,0,0,0,0,158,0,0,0,
0,0,1,0,0,0,0};
static const unsigned char qt_resource_names[] = {
0,
1,0,0,0,47,0,47,0,22,8,5,189,28,0,77,0,
111,0,100,0,101,0,83,0,101,0,108,0,101,0,99,0,
116,0,105,0,111,0,110,0,80,0,111,0,112,0,117,0,
112,0,46,0,113,0,109,0,108,0,8,8,1,90,92,0,
109,0,97,0,105,0,110,0,46,0,113,0,109,0,108,0,
16,3,129,229,220,0,67,0,111,0,110,0,116,0,114,0,
111,0,108,0,80,0,97,0,110,0,101,0,108,0,46,0,
113,0,109,0,108,0,9,0,40,229,188,0,83,0,116,0,
121,0,108,0,101,0,46,0,113,0,109,0,108,0,5,0,
116,90,195,0,109,0,111,0,100,0,101,0,115,0,28,11,
133,131,60,0,72,0,105,0,103,0,104,0,70,0,108,0,
111,0,119,0,78,0,97,0,115,0,97,0,108,0,67,0,
97,0,110,0,110,0,117,0,108,0,97,0,77,0,111,0,
100,0,101,0,46,0,113,0,109,0,108,0,22,10,128,230,
92,0,80,0,114,0,101,0,115,0,115,0,117,0,114,0,
101,0,65,0,115,0,115,0,105,0,115,0,116,0,77,0,
111,0,100,0,101,0,46,0,113,0,109,0,108,0,23,7,
76,154,252,0,80,0,114,0,101,0,115,0,115,0,117,0,
114,0,101,0,67,0,111,0,110,0,116,0,114,0,111,0,
108,0,77,0,111,0,100,0,101,0,46,0,113,0,109,0,
108,0,14,1,85,18,220,0,65,0,108,0,97,0,114,0,
109,0,83,0,111,0,117,0,110,0,100,0,46,0,113,0,
109,0,108,0,8,6,91,155,115,0,99,0,111,0,110,0,
116,0,114,0,111,0,108,0,115,0,16,14,255,196,188,0,
72,0,101,0,97,0,100,0,101,0,114,0,66,0,117,0,
116,0,116,0,111,0,110,0,46,0,113,0,109,0,108,0,
23,14,130,137,252,0,68,0,101,0,118,0,105,0,99,0,
101,0,83,0,116,0,97,0,116,0,117,0,115,0,68,0,
105,0,115,0,112,0,108,0,97,0,121,0,46,0,113,0,
109,0,108,0,24,13,163,169,156,0,80,0,97,0,114,0,
97,0,109,0,101,0,116,0,101,0,114,0,65,0,100,0,
106,0,117,0,115,0,116,0,80,0,111,0,112,0,117,0,
112,0,46,0,113,0,109,0,108,0,14,10,192,150,60,0,
77,0,97,0,105,0,110,0,72,0,101,0,97,0,100,0,
101,0,114,0,46,0,113,0,109,0,108,0,15,10,131,81,
252,0,65,0,108,0,97,0,114,0,109,0,66,0,117,0,
116,0,116,0,111,0,110,0,46,0,113,0,109,0,108,0,
15,4,233,52,220,0,80,0,111,0,112,0,117,0,112,0,
66,0,117,0,116,0,116,0,111,0,110,0,46,0,113,0,
109,0,108,0,11,10,38,168,60,0,70,0,112,0,115,0,
73,0,116,0,101,0,109,0,46,0,113,0,109,0,108,0,
15,2,80,150,60,0,83,0,116,0,101,0,112,0,67,0,
111,0,117,0,110,0,116,0,101,0,114,0,46,0,113,0,
109,0,108,0,13,6,208,27,220,0,66,0,97,0,115,0,
101,0,80,0,111,0,112,0,117,0,112,0,46,0,113,0,
109,0,108,0,14,10,146,127,124,0,66,0,97,0,115,0,
101,0,66,0,117,0,116,0,116,0,111,0,110,0,46,0,
113,0,109,0,108,0,19,5,14,100,220,0,80,0,97,0,
114,0,97,0,109,0,101,0,116,0,101,0,114,0,66,0,
117,0,116,0,116,0,111,0,110,0,46,0,113,0,109,0,
108,0,13,12,134,132,220,0,83,0,99,0,111,0,112,0,
101,0,86,0,105,0,101,0,119,0,46,0,113,0,109,0,
108,0,6,6,232,134,243,0,103,0,114,0,97,0,112,0,
104,0,115,0,11,8,220,13,60,0,84,0,118,0,71,0,
114,0,97,0,112,0,104,0,46,0,113,0,109,0,108,0,
17,12,164,91,156,0,80,0,114,0,101,0,115,0,115,0,
117,0,114,0,101,0,71,0,114,0,97,0,112,0,104,0,
46,0,113,0,109,0,108,0,13,2,6,44,28,0,70,0,
108,0,111,0,119,0,71,0,114,0,97,0,112,0,104,0,
46,0,113,0,109,0,108,0,8,11,123,11,227,0,114,0,
101,0,97,0,100,0,105,0,110,0,103,0,115,0,14,10,
94,83,60,0,73,0,101,0,114,0,68,0,105,0,115,0,
112,0,108,0,97,0,121,0,46,0,113,0,109,0,108,0,
15,15,255,120,28,0,70,0,108,0,111,0,119,0,68,0,
105,0,115,0,112,0,108,0,97,0,121,0,46,0,113,0,
109,0,108,0,14,2,30,89,28,0,80,0,105,0,112,0,
68,0,105,0,115,0,112,0,108,0,97,0,121,0,46,0,
113,0,109,0,108,0,13,5,222,69,188,0,84,0,118,0,
68,0,105,0,115,0,112,0,108,0,97,0,121,0,46,0,
113,0,109,0,108,0,15,10,31,26,60,0,80,0,101,0,
101,0,112,0,68,0,105,0,115,0,112,0,108,0,97,0,
121,0,46,0,113,0,109,0,108,0,13,0,94,69,188,0,
82,0,114,0,68,0,105,0,115,0,112,0,108,0,97,0,
121,0,46,0,113,0,109,0,108,0,15,6,95,115,92,0,
70,0,105,0,79,0,50,0,68,0,105,0,115,0,112,0,
108,0,97,0,121,0,46,0,113,0,109,0,108,0,10,8,
50,125,147,0,112,0,97,0,114,0,97,0,109,0,101,0,
116,0,101,0,114,0,115,0,18,4,120,97,28,0,73,0,
84,0,105,0,109,0,101,0,80,0,97,0,114,0,97,0,
109,0,101,0,116,0,101,0,114,0,46,0,113,0,109,0,
108,0,16,7,192,18,252,0,80,0,105,0,112,0,80,0,
97,0,114,0,97,0,109,0,101,0,116,0,101,0,114,0,
46,0,113,0,109,0,108,0,17,6,230,218,124,0,70,0,
105,0,79,0,50,0,80,0,97,0,114,0,97,0,109,0,
101,0,116,0,101,0,114,0,46,0,113,0,109,0,108,0,
17,6,143,34,252,0,80,0,101,0,101,0,112,0,80,0,
97,0,114,0,97,0,109,0,101,0,116,0,101,0,114,0,
46,0,113,0,109,0,108,0,15,7,212,182,124,0,82,0,
114,0,80,0,97,0,114,0,97,0,109,0,101,0,116,0,
101,0,114,0,46,0,113,0,109,0,108,0,27,15,168,13,
220,0,65,0,108,0,97,0,114,0,109,0,78,0,111,0,
116,0,105,0,102,0,105,0,99,0,97,0,116,0,105,0,
111,0,110,0,66,0,97,0,110,0,110,0,101,0,114,0,
46,0,113,0,109,0,108,0,20,8,126,157,60,0,80,0,
97,0,114,0,97,0,109,0,101,0,116,0,101,0,114,0,
68,0,105,0,115,0,112,0,108,0,97,0,121,0,46,0,
113,0,109,0,108,0,8,5,168,94,188,0,77,0,111,0,
100,0,101,0,46,0,113,0,109,0,108};
static const unsigned char qt_resource_empty_payout[] = { 0, 0, 0, 0, 0 };
QT_BEGIN_NAMESPACE
extern Q_CORE_EXPORT bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
QT_END_NAMESPACE
namespace QmlCacheGeneratedCode {
namespace _controls_Mode_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_ParameterDisplay_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_AlarmNotificationBanner_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_parameters_RrParameter_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_readings_FiO2Display_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__AlarmSound_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_readings_RrDisplay_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_graphs_FlowGraph_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_ScopeView_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _modes_PressureControlMode_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_ParameterButton_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_readings_PeepDisplay_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_parameters_PeepParameter_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Style_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _modes_PressureAssistMode_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__ControlPanel_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_BaseButton_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__main_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_graphs_PressureGraph_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_BasePopup_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_parameters_FiO2Parameter_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_readings_TvDisplay_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__ModeSelectionPopup_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_StepCounter_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _modes_HighFlowNasalCannulaMode_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_parameters_PipParameter_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_FpsItem_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_PopupButton_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_graphs_TvGraph_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_AlarmButton_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_readings_PipDisplay_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_MainHeader_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_readings_FlowDisplay_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_ParameterAdjustPopup_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_DeviceStatusDisplay_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_HeaderButton_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_parameters_ITimeParameter_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _controls_readings_IerDisplay_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/Mode.qml"), &QmlCacheGeneratedCode::_controls_Mode_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/ParameterDisplay.qml"), &QmlCacheGeneratedCode::_controls_ParameterDisplay_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/AlarmNotificationBanner.qml"), &QmlCacheGeneratedCode::_controls_AlarmNotificationBanner_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/parameters/RrParameter.qml"), &QmlCacheGeneratedCode::_controls_parameters_RrParameter_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/readings/FiO2Display.qml"), &QmlCacheGeneratedCode::_controls_readings_FiO2Display_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/AlarmSound.qml"), &QmlCacheGeneratedCode::_0x5f__AlarmSound_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/readings/RrDisplay.qml"), &QmlCacheGeneratedCode::_controls_readings_RrDisplay_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/graphs/FlowGraph.qml"), &QmlCacheGeneratedCode::_controls_graphs_FlowGraph_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/ScopeView.qml"), &QmlCacheGeneratedCode::_controls_ScopeView_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/modes/PressureControlMode.qml"), &QmlCacheGeneratedCode::_modes_PressureControlMode_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/ParameterButton.qml"), &QmlCacheGeneratedCode::_controls_ParameterButton_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/readings/PeepDisplay.qml"), &QmlCacheGeneratedCode::_controls_readings_PeepDisplay_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/parameters/PeepParameter.qml"), &QmlCacheGeneratedCode::_controls_parameters_PeepParameter_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Style.qml"), &QmlCacheGeneratedCode::_0x5f__Style_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/modes/PressureAssistMode.qml"), &QmlCacheGeneratedCode::_modes_PressureAssistMode_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/ControlPanel.qml"), &QmlCacheGeneratedCode::_0x5f__ControlPanel_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/BaseButton.qml"), &QmlCacheGeneratedCode::_controls_BaseButton_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/main.qml"), &QmlCacheGeneratedCode::_0x5f__main_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/graphs/PressureGraph.qml"), &QmlCacheGeneratedCode::_controls_graphs_PressureGraph_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/BasePopup.qml"), &QmlCacheGeneratedCode::_controls_BasePopup_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/parameters/FiO2Parameter.qml"), &QmlCacheGeneratedCode::_controls_parameters_FiO2Parameter_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/readings/TvDisplay.qml"), &QmlCacheGeneratedCode::_controls_readings_TvDisplay_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/ModeSelectionPopup.qml"), &QmlCacheGeneratedCode::_0x5f__ModeSelectionPopup_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/StepCounter.qml"), &QmlCacheGeneratedCode::_controls_StepCounter_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/modes/HighFlowNasalCannulaMode.qml"), &QmlCacheGeneratedCode::_modes_HighFlowNasalCannulaMode_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/parameters/PipParameter.qml"), &QmlCacheGeneratedCode::_controls_parameters_PipParameter_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/FpsItem.qml"), &QmlCacheGeneratedCode::_controls_FpsItem_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/PopupButton.qml"), &QmlCacheGeneratedCode::_controls_PopupButton_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/graphs/TvGraph.qml"), &QmlCacheGeneratedCode::_controls_graphs_TvGraph_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/AlarmButton.qml"), &QmlCacheGeneratedCode::_controls_AlarmButton_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/readings/PipDisplay.qml"), &QmlCacheGeneratedCode::_controls_readings_PipDisplay_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/MainHeader.qml"), &QmlCacheGeneratedCode::_controls_MainHeader_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/readings/FlowDisplay.qml"), &QmlCacheGeneratedCode::_controls_readings_FlowDisplay_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/ParameterAdjustPopup.qml"), &QmlCacheGeneratedCode::_controls_ParameterAdjustPopup_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/DeviceStatusDisplay.qml"), &QmlCacheGeneratedCode::_controls_DeviceStatusDisplay_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/HeaderButton.qml"), &QmlCacheGeneratedCode::_controls_HeaderButton_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/parameters/ITimeParameter.qml"), &QmlCacheGeneratedCode::_controls_parameters_ITimeParameter_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/controls/readings/IerDisplay.qml"), &QmlCacheGeneratedCode::_controls_readings_IerDisplay_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.version = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
QT_PREPEND_NAMESPACE(qRegisterResourceData)(/*version*/0x01, qt_resource_tree, qt_resource_names, qt_resource_empty_payout);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qml)() {
    ::unitRegistry();
    Q_INIT_RESOURCE(qml_qmlcache);
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qml))
int QT_MANGLE_NAMESPACE(qCleanupResources_qml)() {
    Q_CLEANUP_RESOURCE(qml_qmlcache);
    return 1;
}
int QT_MANGLE_NAMESPACE(qInitResources_qmake_qmake_immediate)() {
    ::unitRegistry();
    Q_INIT_RESOURCE(qmake_qmake_immediate_qmlcache);
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qmake_qmake_immediate))
int QT_MANGLE_NAMESPACE(qCleanupResources_qmake_qmake_immediate)() {
    Q_CLEANUP_RESOURCE(qmake_qmake_immediate_qmlcache);
    return 1;
}
