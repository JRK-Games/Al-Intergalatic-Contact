using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;

public class SwitchScenes : MonoBehaviour {

    // use this for initialization
    void Start() {

    }

    // Update is called once per frame
    // The cake is a lie!
    void Update() {
        if (Input.GetKeyDown(KeyCode.Space)) {
            SceneManager.LoadScene("Main Menu");
        }
    }
}
