project(
    'CppUTest',
    'cpp',
    version : '3.8'
)

cpputest_inc = include_directories('cpputest/include')

cpputest_src = files([
    'cpputest//src/CppUTest/CommandLineArguments.cpp',
    'cpputest//src/CppUTest/CommandLineTestRunner.cpp',
    'cpputest//src/CppUTest/JUnitTestOutput.cpp',
    'cpputest//src/CppUTest/MemoryLeakDetector.cpp',
    'cpputest//src/CppUTest/MemoryLeakWarningPlugin.cpp',
    'cpputest//src/CppUTest/SimpleMutex.cpp',
    'cpputest//src/CppUTest/SimpleString.cpp',
    'cpputest//src/CppUTest/TeamCityTestOutput.cpp',
    'cpputest//src/CppUTest/TestFailure.cpp',
    'cpputest//src/CppUTest/TestFilter.cpp',
    'cpputest//src/CppUTest/TestHarness_c.cpp',
    'cpputest//src/CppUTest/TestMemoryAllocator.cpp',
    'cpputest//src/CppUTest/TestOutput.cpp',
    'cpputest//src/CppUTest/TestPlugin.cpp',
    'cpputest//src/CppUTest/TestRegistry.cpp',
    'cpputest//src/CppUTest/TestResult.cpp',
    'cpputest//src/CppUTest/TestTestingFixture.cpp',
    'cpputest//src/CppUTest/Utest.cpp',
])

cpputest_ext_src = files([
    'cpputest//src/CppUTestExt/CodeMemoryReportFormatter.cpp',
    'cpputest//src/CppUTestExt/IEEE754ExceptionsPlugin.cpp',
    'cpputest//src/CppUTestExt/MemoryReportAllocator.cpp',
    'cpputest//src/CppUTestExt/MemoryReporterPlugin.cpp',
    'cpputest//src/CppUTestExt/MemoryReportFormatter.cpp',
    'cpputest//src/CppUTestExt/MockActualCall.cpp',
    'cpputest//src/CppUTestExt/MockExpectedCall.cpp',
    'cpputest//src/CppUTestExt/MockExpectedCallsList.cpp',
    'cpputest//src/CppUTestExt/MockFailure.cpp',
    'cpputest//src/CppUTestExt/MockNamedValue.cpp',
    'cpputest//src/CppUTestExt/MockSupport.cpp',
    'cpputest//src/CppUTestExt/MockSupport_c.cpp',
    'cpputest//src/CppUTestExt/MockSupportPlugin.cpp',
    'cpputest//src/CppUTestExt/OrderedTest.cpp',
])

platform_src = files([
    'cpputest//src/Platforms/Gcc/UtestPlatform.cpp'
])

cpputest_dep = declare_dependency(
    include_directories : [ cpputest_inc ],
	sources             : [ cpputest_src, cpputest_ext_src, platform_src ]
)
