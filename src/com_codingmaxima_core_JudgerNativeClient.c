#include "jni.h"        // JNI header provided by JDK
#include <stdio.h>      // C Standard IO Header
#include <string.h>
#include "com_codingmaxima_core_JudgerNativeClient.h"   // Generated
#include "runner.h"

JNIEXPORT jintArray JNICALL Java_com_codingmaxima_core_JudgerNativeClient_judge(JNIEnv *jniEnv, jclass cls,
    jint max_cpu_time,
    jint max_real_time,
    jint max_memory,
    jint max_stack,
    jint max_process_number,
    jint max_output_size,
    jint memory_limit_check_only,
    jstring exe_path,
    jstring input_file,
    jstring output_file,
    jstring error_file,
    jobjectArray args,
    jobjectArray env,
    jstring log_path,
    jstring seccomp_rule_name,
    jint uid,
    jint gid) {

    struct config _config;
    struct result _result = {0, 0, 0, 0, 0, 0, 0};

    if (max_cpu_time > 0) {
        _config.max_cpu_time = max_cpu_time;
    } else {
        _config.max_cpu_time = UNLIMITED;
    }

    if (max_real_time > 0) {
        _config.max_real_time = max_real_time;
    } else {
        _config.max_real_time = UNLIMITED;
    }

    if (max_memory > 0) {
        _config.max_memory = max_memory;
    } else {
        _config.max_memory = UNLIMITED;
    }

    if (memory_limit_check_only > 0) {
        _config.memory_limit_check_only = 1;
    } else {
        _config.memory_limit_check_only = 0;
    }

    if (max_stack > 0) {
        _config.max_stack = max_stack;
    } else {
        _config.max_stack = 16 * 1024 * 1024;
    }

    if (max_process_number > 0) {
        _config.max_process_number = max_process_number;
    } else {
        _config.max_process_number = UNLIMITED;
    }

    if (max_output_size > 0) {
        _config.max_output_size = max_output_size;
    } else {
        _config.max_output_size = UNLIMITED;
    }

    _config.exe_path = (char *)((*jniEnv)->GetStringUTFChars(jniEnv, exe_path, NULL));

    if ((*jniEnv)->GetStringLength(jniEnv, input_file) > 0) {
        _config.input_path = (char *)((*jniEnv)->GetStringUTFChars(jniEnv, input_file, NULL));
    } else {
        _config.input_path = "/dev/stdin";
    }
    if ((*jniEnv)->GetStringLength(jniEnv, output_file) > 0) {
        _config.output_path = (char *)((*jniEnv)->GetStringUTFChars(jniEnv, output_file, NULL));
    } else {
        _config.output_path = "/dev/stdout";
    }
    if ((*jniEnv)->GetStringLength(jniEnv, error_file) > 0) {
        _config.error_path = (char *)((*jniEnv)->GetStringUTFChars(jniEnv, error_file, NULL));
    } else {
        _config.error_path = "/dev/stderr";
    }

    _config.args[0] = _config.exe_path;
    int i = 1;
    int argsCount = (*jniEnv)->GetArrayLength(jniEnv, args);
    if (argsCount > 0) {
        for (; i < argsCount + 1; i++) {
            jstring jargsItem = (jstring) ((*jniEnv)->GetObjectArrayElement(jniEnv, args, i - 1));
             char *cargsItem = (char *)((*jniEnv)->GetStringUTFChars(jniEnv, jargsItem, NULL));
             //char tempcargsItem[(*jniEnv)->GetStringLength(jniEnv, jargsItem)];
            _config.args[i] = cargsItem; //strcpy(tempcargsItem, cargsItem);

            //(*jniEnv)->ReleaseStringUTFChars(jniEnv, jargsItem, cargsItem);
        }
    }
    _config.args[i] = NULL;

    i = 0;
    int envCount = (*jniEnv)->GetArrayLength(jniEnv, env);
    if (envCount > 0) {
        for (; i < envCount; i++) {
            jstring jenvItem = (jstring) ((*jniEnv)->GetObjectArrayElement(jniEnv, env, i));
             char *cenvItem = (char *)((*jniEnv)->GetStringUTFChars(jniEnv, jenvItem, NULL));
             //char tempcEnvItem[(*jniEnv)->GetStringLength(jniEnv, jenvItem)];
            _config.env[i] = cenvItem; //strcpy(tempcEnvItem, cenvItem);

            //(*jniEnv)->ReleaseStringUTFChars(jniEnv, jenvItem, cenvItem);
        }
    }
    _config.env[i] = NULL;

    if ((*jniEnv)->GetStringLength(jniEnv, log_path) > 0) {
        _config.log_path = (char *)((*jniEnv)->GetStringUTFChars(jniEnv, log_path, NULL));
    } else {
        _config.log_path = "judger.log";
    }

    _config.seccomp_rule_name = NULL;

    if (uid > 0) {
        _config.uid = uid;
    }
    else {
        _config.uid = 0;
    }
    if(gid > 0) {
        _config.gid = gid;
    }
    else {
        _config.gid = 0;
    }

    run(&_config, &_result);

    // Release resources
    (*jniEnv)->ReleaseStringUTFChars(jniEnv, exe_path, _config.exe_path);
    (*jniEnv)->ReleaseStringUTFChars(jniEnv, input_file, _config.input_path);
    (*jniEnv)->ReleaseStringUTFChars(jniEnv, output_file, _config.output_path);
    (*jniEnv)->ReleaseStringUTFChars(jniEnv, error_file, _config.error_path);
    (*jniEnv)->ReleaseStringUTFChars(jniEnv, log_path, _config.log_path);
    int i;
    for (i = 0; i < argsCount; i++) {
        /*jstring jargsItem = (jstring) ((*jniEnv)->GetObjectArrayElement(jniEnv, args, i));
        (*jniEnv)->ReleaseStringUTFChars(jniEnv, jargsItem, _config.args[i]);*/
        _config.args[i] = NULL;
    }
    for (i = 0; i < envCount; i++) {
        /*jstring jenvItem = (jstring) ((*jniEnv)->GetObjectArrayElement(jniEnv, env, i));
        (*jniEnv)->ReleaseStringUTFChars(jniEnv, jenvItem, _config.env[i]);*/
        _config.env[i] = NULL;
    }

    jint jResult[] = {_result.cpu_time, _result.real_time, _result.memory, _result.signal, _result.exit_code, _result.error, _result.result};

    jintArray outJNIArray = (*jniEnv)->NewIntArray(jniEnv, 7);  // allocate
    if (NULL == outJNIArray) return NULL;
    (*jniEnv)->SetIntArrayRegion(jniEnv, outJNIArray, 0 , 7, jResult);  // copy

    return outJNIArray;
}
