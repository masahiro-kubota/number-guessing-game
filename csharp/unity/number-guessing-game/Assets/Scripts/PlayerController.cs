using System.Collections;
using System.Collections.Generic;
using System.Xml.Serialization;
using UnityEngine;
using UnityEngine.InputSystem;
using TMPro;
using UnityEngine.Video;

public class PlayerController : MonoBehaviour
{
    public float speed = 0;
    public TextMeshProUGUI countText;
    public GameObject winTextObject;
    private Rigidbody rb;
    private int count;

    private int secretNumber;

    private bool isSuccess;
    private float movementX;
    private float movementY;

    // Start is called before the first frame update
    void Start()
    {
        
        
        rb = GetComponent<Rigidbody>();
        count = 0;
        isSuccess = false;
        secretNumber = 43;

        winTextObject.SetActive(false);
    }

    void OnMove(InputValue movementValue)
    {
      Vector2 movementVector = movementValue.Get<Vector2>();
      movementX = movementVector.x;
      movementY = movementVector.y;
    }

    void SetCountText()
    {
      countText.text = "Incorrect";
      if (isSuccess)
      {
        countText.text = "Correct";
        winTextObject.SetActive(true);
        Destroy(GameObject.FindGameObjectWithTag("Enemy"));
      }
    }

    void FixedUpdate()
    {
      Vector3 movement = new Vector3(movementX, 0.0f, movementY); 
      rb.AddForce(movement * speed);
    }

    private void OnCollisionEnter(Collision other)
    {
      if (other.gameObject.CompareTag("Enemy"))
      {
        gameObject.SetActive(false);
        winTextObject.SetActive(true);
        winTextObject.GetComponent<TextMeshProUGUI>().text = "Game Over!";
      }
    }

    private void OnTriggerEnter(Collider other)
    {
      if (other.gameObject.CompareTag("PickUp"))
      {
        other.gameObject.SetActive(false);
        count++;
        SetCountText();
        string tmpNumber = other.GetComponentInChildren<TextMeshPro>().text;
        Debug.Log(tmpNumber);
        if (int.Parse(tmpNumber) == secretNumber)
        {
          isSuccess = true;
          Debug.Log("It's a match!");
          SetCountText();
        }
      }
    }


}
