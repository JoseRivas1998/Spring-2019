using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFollow : MonoBehaviour
{

    public GameObject toFollow;
    public Vector3 offset;
    public float speed;

    private Vector3 goalPosition;

    // Start is called before the first frame update
    void Start()
    {
        goalPosition = new Vector3();
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 gameObjectPosition = toFollow.transform.position;
        goalPosition = gameObjectPosition + offset;
        transform.position += (goalPosition - transform.position) / speed;
        transform.LookAt(gameObjectPosition);
    }
}
