using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Experimental.UIElements;

public class PlayerControl : MonoBehaviour
{
    // Set these bois in editor
    public float speed = 6.0f;
    public float sensitivity = 120.0f;
    public float gravity = 20.0f;
    public float jumpSpeed = 10.0f;
    
    private CharacterController controller;
    private Camera cam;

    private Vector3 direction = Vector3.zero; // This is really velocity but shwatevs
    
    // Start is called before the first frame update
    void Start()
    {
        controller = GetComponent<CharacterController>();
        cam = GetComponentInChildren<Camera>();
    }

    // Update is called once per frame
    void Update()
    {
        float dt = Time.deltaTime;
        Move(dt);           
        Look(dt);
    }

    private void Move(float dt)
    {
        float horizontal = Input.GetAxis("Horizontal");
        float vertical = Input.GetAxis("Vertical");
        Vector3 inputVector = transform.forward * vertical + transform.right * horizontal;
        Vector3 movement = inputVector * speed;
        direction.x = movement.x;
        direction.z = movement.z;
        if (controller.isGrounded)
        {
            if (Input.GetKey("space"))
            {
                direction.y = jumpSpeed;
            }
            else
            {
                direction.y = 0;
            }
        }

        controller.Move(direction * dt);
        direction.y -= gravity * dt;
    }

    private void Look(float dt)
    {
        float mouseX = Input.GetAxis("Mouse X");
        float mouseY = -Input.GetAxis("Mouse Y"); // Gimme the world coordinates
        float transformRotation = mouseX * sensitivity * dt;
        float camRotation = mouseY * sensitivity * dt;
        transform.Rotate(0, transformRotation, 0);
        cam.transform.Rotate(camRotation, 0, 0);
    }
    
}
